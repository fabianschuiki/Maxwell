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
		
		//Split up the input files into their root entities.
		$nodeIDs = array();
		$legend = "";
		foreach ($inputFiles as $inputFile) {
			static::debug("splitting $inputFile");
			
			$input = new InputFile($inputFile, $this->buildDir);
			$input->loadCached();
			if ($issues->dumpAndCheck()) return;
			
			$importedRoots = array();
			$importedNodes = array();
			foreach ($input->importList as $name => $path) {
				$import = new ImportedFile($path, $this->buildDir);
				$import->load();
				$importedRoots[] = $import->let;
				foreach ($import->let->children() as $node) $importedNodes[$node->id] = $node;
			}
			foreach ($importedRoots as $root) {
				$root->bindProxies($importedNodes);
				$root->reduce();
				if ($issues->dumpAndCheck()) return;
			}
			
			$input->let->bindProxies($importedNodes);
			$input->let->reduce();
			if ($issues->dumpAndCheck()) return;
			
			$input->let->importedRoots = $importedRoots;
			$input->let->bind();
			$input->let->reduce();
			$input->let->importedRoots = null;
			if ($issues->dumpAndCheck()) return;
			
			$input->saveLET();
			
			foreach ($input->let->children() as $node) {
				$root = new \LET\Root;
				$node->scope = $root->scope;
				$node->subscope->outer = $node->scope;
				$root->scope->add($node);
				static::debug("- {$node->id}");
				$legend .= "{$node->id}  {$node->desc()}\n";
				
				$e = new Entity($node->id, $this->buildDir);
				$e->node = $root;
				$e->save();
				$nodeIDs[] = $node->id;
				//foreach ($root->externalNodes as $id) static::debug("  - uses $id");
			}
		}
		file_put_contents("{$this->buildDir}/legend.txt", $legend);
		
		//Iterate through the nodes and analyze each.
		$specs = array();
		foreach ($nodeIDs as $id) {
			static::debug("analyzing $id");
			
			$input = new Entity($id, $this->buildDir);
			$input->load();
			$input->loadExternalNodeIDs();
			if ($issues->dumpAndCheck()) return;
			
			$externalEntities = array();
			$externalNodes = array();
			foreach ($input->externalNodeIDs as $eid) {
				static::debug("- importing $eid");
				$e = new Entity($eid, $this->buildDir);
				$e->loadInterface();
				$e->loadSpecs();
				$externalEntities[] = $e;
				$externalNodes[$eid] = array_pop($e->node->children());
			}
			foreach ($externalEntities as $entity) {
				$entity->node->bindProxies($externalNodes);
				$entity->node->reduce();
			}
			if ($issues->dumpAndCheck()) return;
			
			$input->node->bindProxies($externalNodes);
			$input->node->reduce();
			if ($issues->dumpAndCheck()) return;
			
			$input->node->importedRoots = array_map(function($i){ return $i->node; }, $externalEntities);
			$analyzer = new \Analyzer;
			$analyzer->issues = $issues;
			$analyzer->root   = $input->node;
			$analyzer->run();
			$input->node->importedRoots = null;
			if ($issues->dumpAndCheck()) return;
			
			foreach ($externalEntities as $entity) {
				$entity->saveSpecs();
				if ($entity->node->specializations) $specs = array_merge($specs, $entity->node->specializations);
			}
			$input->save();
		}
		
		//Show the specs.
		if (count($specs)) static::debug("specializations:");
		foreach ($specs as $id => $spec) static::debug("- $id: {$spec->details()}");
		
		//Sort the specializations according to the type they specialize.
		$sortedSpecs = array();
		foreach ($specs as $id => $spec) $sortedSpecs[$spec->originalID][$id] = $spec;
		
		//Specialize the required nodes.
		foreach ($sortedSpecs as $id => $nodeSpecs) {
			static::say("specializing $id");
			
			//This is just a dumb copy of above. This will be merged into the analysis stage.
			$input = new Entity($id, $this->buildDir);
			$input->load();
			$input->loadExternalNodeIDs();
			if ($issues->dumpAndCheck()) return;
			
			//Load additional node IDs that might be required by the specialization.
			$externalNodeIDs = $input->externalNodeIDs;
			foreach ($nodeSpecs as $specID => $spec)	$spec->gatherExternalNodeIDs($externalNodeIDs);
			$externalNodeIDs = array_unique(array_diff($externalNodeIDs, array($id)));
			
			//Import external nodes.
			$externalEntities = array();
			$externalNodes = array($id => array_pop($input->node->children()));
			foreach ($externalNodeIDs as $eid) {
				static::debug("- importing $eid");
				$e = new Entity($eid, $this->buildDir);
				$e->loadInterface();
				$externalEntities[] = $e;
				$externalNodes[$eid] = array_pop($e->node->children());
			}
			foreach ($externalEntities as $entity) {
				$entity->node->bindProxies($externalNodes);
				$entity->node->reduce();
			}
			if ($issues->dumpAndCheck()) return;
			
			$input->node->bindProxies($externalNodes);
			$input->node->reduce();
			if ($issues->dumpAndCheck()) return;
			//<- until here
			
			//Bind the specs proxies.
			foreach ($nodeSpecs as $specID => $spec) {
				$spec->bindProxies($externalNodes);
				$spec->reduce();
				if ($issues->dumpAndCheck()) return;
				
				$spec->bind();
				$spec->reduce();
				if ($issues->dumpAndCheck()) return;
				
				echo "- $specID became {$spec->desc()}\n";
			}
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