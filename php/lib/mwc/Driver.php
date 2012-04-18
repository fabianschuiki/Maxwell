<?php
namespace mwc;

class Driver
{
	private $inputFiles    = array();
	private $outputPath    = null;
	private $buildDir      = null;
	private $dumpStats     = false;
	private $upToStage     = 2;
	private $ignoreImports = false;
	
	public function configure(array $args)
	{
		while (count($args)) {
			$arg = array_shift($args);
			if ($arg[0] == "-") {
				switch ($arg) {
					case "-o": {
						if (!count($args)) static::error("-o requires output path");
						$this->outputPath = array_shift($args);
					} break;
					case "-b": {
						if (!count($args)) static::error("-b requires a build directory");
						$this->buildDir = array_shift($args);
					} break;
					case "-p": $this->upToStage = 1; break; //parse only
					case "-a": $this->upToStage = 2; break; //parse and analyze only
					case "--stats": $this->dumpStats = true; break;
					case "--debug": global $debugMode; $debugMode = true; break;
					case "--ignore-imports": $this->ignoreImports = true; break;
					default: {
						static::error("unknown option '$arg'");
					} break;
				}
			} else {
				$this->inputFiles[] = $arg;
			}
		}
	}
	
	public function run()
	{
		global $argv;
		$mwc = escapeshellarg($argv[0]);
		
		if (!$this->inputFiles) static::error("no input files");
		if (!$this->outputPath) $this->outputPath = preg_replace('/\.mw$/', '', $this->inputFiles[0]);
		if (!$this->buildDir)   $this->buildDir   = dirname($this->outputPath);
		if (!is_dir($this->buildDir)) static::error("build directory '{$this->buildDir}' does not exist");
		
		global $issues;
		$issues = new \IssueList;
		
		//Open the source files.
		$inputs = array();
		foreach ($this->inputFiles as $inputFile) {
			if (!file_exists($inputFile)) static::error("source file '$inputFile' does not exist");
			$input = new InputFile($inputFile, $this->buildDir);
			$input->load();
			$inputs[] = $input;
		}
		if ($issues->dumpAndCheck()) return;
		
		//Feed each file through the lexer, parse it and build the LET.
		foreach ($inputs as $input) {
			$input->parse();
			$input->saveLET();
			$input->saveInterface();
		}
		if ($this->upToStage == 1) return;
		
		//Resolve the imports.
		$imported = array();
		$importsToProcess = array();
		foreach ($inputs as $input) {
			$importsToProcess = array_merge($importsToProcess, $input->let->imports);
		}
		while ($importsToProcess) {
			$import = array_shift($importsToProcess);
			if (!isset($imported[strval($import->name)])) {
				$file = new ImportedFile(dirname($input->path)."/{$import->name}.mw", $this->buildDir);
				$imported[strval($import->name)] = $file;
				
				$intf = $file->interfacePath();
				if (!file_exists($intf) || filemtime($intf) < filemtime($file->path)) {
					$cmd = "$mwc -p -b ".escapeshellarg($this->buildDir)." ".escapeshellarg($file->path);
					static::say("parsing {$file->path}");
					//debug("$cmd\n");
					$result = 0;
					passthru($cmd, $result);
					if ($result != 0) static::error("unable to parse {$file->path}");
				}
				$file->load();
				if ($issues->dumpAndCheck()) return;
				
				$importsToProcess = array_merge($importsToProcess, $file->let->imports);
			}
		}
		foreach ($inputs as $input) {
			$names = array_map(function($i){ return strval($i->name); }, $input->let->imports);
			$imports = array();
			foreach ($names as $name) {
				assert(isset($imported[$name]));
				$imports[] = $imported[$name]->let;
			}
			$input->imported = $imports;
		}
		
		//Analysis iteration starts here:
		//TODO: analyze each imported file, starting with the last (generally the least referenced one) through another call to mwc, until no more specializations are issued.
		//Analyze the imported files.
		if (!$this->ignoreImports) {
			$toAnalyze = $imported;
			while (count($toAnalyze)) {
				$i = array_pop($toAnalyze);
				$cmd = "$mwc -a --ignore-imports -b ".escapeshellarg($this->buildDir)." ".escapeshellarg($i->path);
				static::say("analyzing {$i->path}");
				//debug("$cmd\n");
				$result = 0;
				passthru($cmd, $result);
				if ($result != 0) static::error("unable to analyze {$file->path}");
			}
		}
		
		//TODO: for each imported file, load the .specs file into the specializations array.
		//foreach ($imported as $i) $i->loadSpecs();
		
		//Analyze each file.
		foreach ($inputs as $input) {
			$input->analyze();
			$input->saveLET();
			$input->saveInterface();
		}
		
		//NOTE: every imported file's specializations array now contains the required specializations from the other imported files, as well as our input files.
		//Perform specializations in imported files.
		foreach ($imported as $i) $i->saveSpecs();
		
		//NOTE: that we will loop back up where the imported files are re-analyzed, which causes them to specialize whatever is stored in the .spec files.
		
		//Analysis iteration loops back up from here.
		
		if ($this->upToStage == 2) return;
	}
	
	private function writeLETFile($file)
	{
		file_put_contents($this->buildDir."/".basename($file->source->path, '.mw').".let", serialize($file->let));
	}
	
	static public function error($msg) { echo "mwc: $msg\n"; exit(1); }
	static public function say($msg)   { echo "mwc: $msg\n"; }
	static public function debug($msg) { debug("mwc: $msg\n"); }
}

function debug($msg)
{
	global $debugMode;
	if (!$debugMode) return;
	echo $msg;
}