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
			$inputFiles[] = $inputFile;
			
			//Create the input file instance.
			$input = new InputFile($inputFile, $this->buildDir);
			//if ($input->cacheUpToDate()) continue;
			
			//Parse the file.
			static::debug("parsing $inputFile");
			if (!file_exists($inputFile)) static::error("source file '$inputFile' does not exist");
			$input->load();
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
		$specs = array();
		$nodes = array();
		foreach ($inputFiles as $inputFile) {
			static::debug("analyzing $inputFile");
			
			$input = new InputFile($inputFile, $this->buildDir);
			$input->loadCached();
			if ($issues->dumpAndCheck()) return;
			
			//Load the required interfaces.
			$imports = array();
			$importedNodes = array();
			foreach ($input->let->imports as $import) {
				$path = $input->importList[strval($import->name)];
				static::debug("- loading interface $path");
				$f = new ImportedFile($path, $this->buildDir);
				$f->load();
				$imports[] = $f;
				foreach ($f->let->children() as $node) $importedNodes[$node->id] = $node;
			}
			if ($issues->dumpAndCheck()) return;
			
			foreach ($importedNodes as $id => $node) {
				$node->bindProxies($importedNodes);
				$node->bind();
				$node->reduce();
				if ($issues->dumpAndCheck()) return;
				static::debug("  - imported $id: {$node->desc()}");
			}
			
			$input->importedFiles = $imports;
			
			//Analyze.
			$input->analyze();
			$input->saveLET();
			if ($issues->dumpAndCheck()) return;
			
			//Keep the specialization requests for later.
			foreach ($imports as $import) $specs = array_merge($specs, $import->let->specializations);
			
			//Disassemble the root scope into individual entities.
			foreach ($input->let->children() as $node) {
				$root = new \LET\Root;
				$node->scope = $root->scope;
				$root->scope->add($node);
				
				$e = new Entity($node->id, $this->buildDir);
				$e->node = $root;
				$e->save();
				$nodes[] = $node->id;
			}
		}
		
		//Show the specs.
		if (count($specs)) static::debug("specializations:");
		foreach ($specs as $spec) static::debug("- {$spec->details()}");
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