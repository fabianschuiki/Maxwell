<?php
namespace mwc;

class Driver
{
	private $inputFiles    = array();
	private $outputPath    = null;
	private $buildDir      = null;
	private $dumpStats     = false;
	
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
					case "--stats": $this->dumpStats = true; break;
					case "--debug": global $debugMode; $debugMode = true; break;
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
		
		//Process the input files and resovle the imports.
		$inputFiles = array();
		$inputFilesLeft = $this->inputFiles;
		while ($inputFilesLeft) {
			$inputFile = array_shift($inputFilesLeft);
			static::debug("parsing $inputFile");
			
			//Load the input file.
			if (!file_exists($inputFile)) static::error("source file '$inputFile' does not exist");
			$input = new InputFile($inputFile, $this->buildDir);
			$input->load();
			$inputFiles[] = $inputFile;
			if ($issues->dumpAndCheck()) return;
			
			//Parse and process.
			$input->parse();
			$input->bindLocally();
			if ($issues->dumpAndCheck()) return;
			
			//Dump the preliminary LET and interface.
			$input->saveLET();
			$input->saveInterface();
			
			//Resolve the imports.
			$importList = array();
			$importsToProcess = $input->let->imports;
			while ($importsToProcess) {
				$import = array_shift($importsToProcess);
				$name   = strval($import->name);
				$path   = dirname($input->path)."/{$name}.mw";
				if (!file_exists($path)) {
					$issues[] = new \Issue(
						'error',
						"Nothing found to import named '{$name}'.",
						$import
					);
				}
				if (!in_array($path, $inputFiles)) $inputFilesLeft[] = $path;
				$importList[$name] = $path;
			}
			$input->importList = $importList;
			$input->saveImportList();
			if ($issues->dumpAndCheck()) return;
		}
		
		//Perform the initial analysis for all files.
		foreach ($inputFiles as $inputFile) {
			static::debug("analyzing $inputFile");
			
			$input = new InputFile($inputFile, $this->buildDir);
			$input->loadCached();
			if ($issues->dumpAndCheck()) return;
			
			//Load the required interfaces.
			$imports = array();
			foreach ($input->let->imports as $import) {
				$path = $input->importList[strval($import->name)];
				static::debug("- loading interface $path");
				$f = new ImportedFile($path, $this->buildDir);
				$f->load();
				$imports[] = $f;
			}
			$input->importedFiles = $imports;
			if ($issues->dumpAndCheck()) return;
		}
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