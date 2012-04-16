<?php
namespace mwc;

class Driver
{
	private $inputFiles = array();
	private $outputPath = null;
	private $buildDir   = null;
	private $dumpStats  = false;
	
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
		$files = array();
		foreach ($this->inputFiles as $inputFile) {
			if (!file_exists($inputFile)) static::error("source file '$inputFile' does not exist");
			$file = new \SourceFile;
			$file->path = $inputFile;
			$file->load();
			
			$f = new \stdClass;
			$f->file = $file;
			$files[] = $f;
		}
		if ($issues->dumpAndCheck()) return;
		
		//Feed each file through the lexer, parse it and build the LET.
		foreach ($files as $file) {
			$lexer = new \Lexer;
			$lexer->file = $file->file;
			$lexer->run();
			if ($issues->dumpAndCheck()) return;
			
			$parser = new \Parser;
			$parser->tokens = $lexer->tokens;
			$parser->issues = $issues;
			$parser->run();
			if ($issues->dumpAndCheck()) return;
			
			$let = new \LET\Root($parser->nodes);
			if ($issues->dumpAndCheck()) return;
			
			$file->ast = $parser->nodes;
			$file->let = $let;
			$this->writeLETFile($file);
		}
		
		//Analyze each file.
		foreach ($files as $file) {
			$analyzer = new \Analyzer;
			$analyzer->issues = $issues;
			$analyzer->root   = $file->let;
			$analyzer->run();
			if ($issues->dumpAndCheck()) return;
			if ($this->dumpStats) $analyzer->dumpStats();
			$this->writeLETFile($file);
		}
	}
	
	private function writeLETFile($file)
	{
		file_put_contents($this->buildDir."/".basename($file->file->path, '.mw').".let", serialize($file->let));
	}
	
	static public function error($msg) { die("mwc: $msg\n"); }
	static public function say($msg)   { echo "mwc: $msg\n"; }
}