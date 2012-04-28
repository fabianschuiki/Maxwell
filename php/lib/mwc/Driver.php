<?php
namespace mwc;

class Driver
{
	public $inputFiles    = array();
	public $outputPath    = null;
	public $buildDir      = null;
	public $dumpStats     = false;
	
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
		
		//Create some extra directories if required.
		static::makeDirectory($this->buildDir."/input");
		static::makeDirectory($this->buildDir."/entities");
		static::makeDirectory($this->buildDir."/debug");
		
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
		
		//Iterate through the nodes and analyze each.
		do {
			//pause();
			file_put_contents("{$this->buildDir}/legend.txt", $legend);
			$specs = array();
			foreach ($nodeIDs as $id) {
				static::debug("analyzing $id");
				
				$input = new Entity($id, $this->buildDir);
				$input->load($externalEntities, $externalNodes);
				/*$input->load();
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
					$externalNodes[$eid] = $e->mainNode();
				}
				foreach ($externalEntities as $entity) {
					$entity->node->bindProxies($externalNodes);
					$entity->node->reduce();
					
					$entity->node->bind();
					$entity->node->reduce();
				}
				if ($issues->dumpAndCheck()) return;
				
				$input->node->bindProxies($externalNodes);
				$input->node->reduce();
				if ($issues->dumpAndCheck()) return;*/
				
				$input->node->importedRoots = array_map(function($i){ return $i->node; }, $externalEntities);
				$analyzer = new \Analyzer;
				$analyzer->issues = $issues;
				$analyzer->root   = $input->node;
				$analyzer->run();
				$input->node->importedRoots = null;
				
				foreach ($externalEntities as $entity) {
					$entity->saveSpecs();
					if ($entity->node->specializations) $specs = array_merge($specs, $entity->node->specializations);
				}
				$input->save();
				if ($issues->dumpAndCheck()) return;
			}
			
			//Filter the specializations to exclude the ones that already exist.
			foreach ($specs as $id => $spec) if (in_array($id, $nodeIDs)) unset($specs[$id]);
			
			//Show the specs.
			if (count($specs)) static::debug("specializations:");
			foreach ($specs as $id => $spec) static::debug("- $id: {$spec->details()}");
			
			//Sort the specializations according to the type they specialize.
			$sortedSpecs = array();
			foreach ($specs as $id => $spec) $sortedSpecs[$spec->originalID][$id] = $spec;
			
			//Specialize the required nodes.
			foreach ($sortedSpecs as $id => $nodeSpecs) {
				static::say("specializing $id");
				
				//Gather external nodes required by the specializations.
				$additional = array();
				foreach ($nodeSpecs as $specID => $spec)	$spec->gatherExternalNodeIDs($additional);
				
				//This is just a dumb copy of above. This will be merged into the analysis stage.
				$input = new Entity($id, $this->buildDir);
				$input->load($externalEntities, $externalNodes, $additional);
				/*$input->load();
				$input->loadExternalNodeIDs();
				if ($issues->dumpAndCheck()) return;
				
				//Load additional node IDs that might be required by the specialization.
				$externalNodeIDs = $input->externalNodeIDs;
				foreach ($nodeSpecs as $specID => $spec)	$spec->gatherExternalNodeIDs($externalNodeIDs);
				$externalNodeIDs = array_unique(array_diff($externalNodeIDs, array($id)));
				
				//Import external nodes.
				$externalEntities = array();
				$externalNodes = array($id => $input->mainNode());
				foreach ($externalNodeIDs as $eid) {
					$e = new Entity($eid, $this->buildDir);
					$e->loadInterface();
					$externalEntities[] = $e;
					$externalNodes[$eid] = $e->mainNode();
					static::debug("- imported $eid  {$e->mainNode()->desc()}");
				}
				foreach ($externalEntities as $entity) {
					$entity->node->bindProxies($externalNodes);
					$entity->node->reduce();
					
					$entity->node->bind();
					$entity->node->reduce();
				}
				if ($issues->dumpAndCheck()) return;
				
				$input->node->bindProxies($externalNodes);
				$input->node->reduce();
				if ($issues->dumpAndCheck()) return;*/
				//<- until here
				
				//Specialize.
				$specializedNodes = array();
				foreach ($nodeSpecs as $specID => $spec) {
					$spec->bindProxies($externalNodes);
					$spec->reduce();
					if ($issues->dumpAndCheck()) return;
					
					$spec->bind();
					$spec->reduce();
					if ($issues->dumpAndCheck()) return;
					
					static::debug("- {$spec->details()}  @$specID");
					$result = null;
					if ($spec instanceof \LET\MemberConstrainedType) {
						$result = $input->mainNode()->specialize($spec, $specializedNodes);
					} else if ($spec instanceof \LET\FuncType) {
						$result = $input->mainNode()->specialize($spec, $specializedNodes);
					} else {
						static::error("specialization ".get_class($spec)." not supported");
					}
					assert($result);
					$result->id = $specID;
					static::debug("  => {$result->desc()}");
					
					//Create the new node file for the specialization.
					$root = new \LET\Root;
					$result->scope = $root->scope;
					$result->subscope->outer = $result->scope;
					$root->scope->add($result);
					$legend .= "{$result->id}  {$result->desc()}\n";
					
					$e = new Entity($result->id, $this->buildDir);
					$e->node = $root;
					$e->save();
					$nodeIDs[] = $result->id;
				}
			}
		} while (count($specs));
		
		//Compile the nodes to C.
		$compiler = new Compiler($this);
		$compiler->compile($nodeIDs);
	}
	
	static public function error($msg) { echo "mwc: $msg\n"; exit(1); }
	static public function say($msg)   { echo "mwc: $msg\n"; }
	static public function debug($msg) { debug("mwc: $msg\n"); }
	
	static public function makeDirectory($dir)
	{
		if (file_exists($dir)) return;
		if (!mkdir($dir)) static::error("unable to make directory {$dir}");
	}
}

function debug($msg)
{
	global $debugMode;
	if (!$debugMode) return;
	echo $msg;
}

function pause()
{
	readline("[\033[36mpaused - press enter to continue\033[0m]");
}