<?php
namespace mwc;

class Driver
{
	private $inputFiles = array();
	private $outputPath = null;
	private $buildDir   = null;
	private $dumpStats  = false;
	private $upToStage  = 2;
	
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
				}
			} else {
				$this->inputFiles[] = $arg;
			}
		}
	}
	
	public function run()
	{
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
				if (/*!file_exists($intf) || filemtime($intf) < filemtime($file->path)*/true) {
					global $argv;
					static::say("parsing {$file->path}");
					$cmd = escapeshellarg($argv[0])." -p -b ".escapeshellarg($this->buildDir)." ".escapeshellarg($file->path);
					passthru($cmd);
				}
				$file->load();
				if ($issues->dumpAndCheck()) return;
				
				$importsToProcess = array_merge($importsToProcess, $file->let->imports);
			}
		}
		
		//Analyze each file.
		foreach ($inputs as $input) {
			$input->analyze();
			$input->saveLET();
			$input->saveInterface();
		}
		if ($this->upToStage == 2) return;
	}
	
	private function writeLETFile($file)
	{
		file_put_contents($this->buildDir."/".basename($file->source->path, '.mw').".let", serialize($file->let));
	}
	
	static public function error($msg) { die("mwc: $msg\n"); }
	static public function say($msg)   { echo "mwc: $msg\n"; }
}

function debug($msg)
{
	global $debugMode;
	if (!$debugMode) return;
	echo $msg;
}