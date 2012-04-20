<?php
namespace mwc;

class InputFile extends SourceFile
{
	public $source;
	public $ast;
	public $let;
	public $importList;
	public $importedFiles;
	
	public function load()
	{
		if ($this->source) return;
		
		$f = new \SourceFile;
		$f->path = $this->path;
		$f->load();
		$this->source = $f;
	}
	
	public function loadCached()
	{
		if ($this->let) return;
		
		$let = $this->letPath();
		if (!file_exists($let)) Driver::error("parsed LET should exist at '$let', but does not");
		$this->let = unserialize(file_get_contents($let));
		assert($this->let instanceof \LET\Root);
		
		$imports = $this->importListPath();
		if (!file_exists($imports)) Driver::error("list of imports should exist at '$imports', but does not");
		$this->importList = unserialize(file_get_contents($imports));
		assert(is_array($this->importList));
	}
	
	public function cacheUpToDate()
	{
		if (!file_exists($this->letPath())) return false;
		return filemtime($this->path) < filectime($this->letPath());
	}
	
	public function parse()
	{
		global $issues;
		
		$lexer = new \Lexer;
		$lexer->file = $this->source;
		$lexer->run();
		if ($issues->dumpAndCheck()) return;
		
		$parser = new \Parser;
		$parser->tokens = $lexer->tokens;
		$parser->issues = $issues;
		$parser->run();
		if ($issues->dumpAndCheck()) return;
		$this->ast = $parser->nodes;
		
		$let = new \LET\Root($parser->nodes);
		if ($issues->dumpAndCheck()) return;
		$this->let = $let;
	}
	
	public function bindLocally()
	{
		$this->let->bind(true);
		$this->let->reduce();
	}
	
	public function analyze()
	{
		global $issues;
		assert($this->let instanceof \LET\Root);
		
		$this->let->importedRoots = array_map(function($f){ return $f->let; }, $this->importedFiles);
		
		$analyzer = new \Analyzer;
		$analyzer->issues = $issues;
		$analyzer->root   = $this->let;
		$analyzer->run();
		if ($issues->dumpAndCheck()) return;
		
		$this->let->importedRoots = null;
	}
	
	public function saveLET()
	{
		file_put_contents($this->letPath(), serialize($this->let));
		file_put_contents($this->letPath().".html", \Dump::let($this->let));
	}
	
	public function saveInterface()
	{
		$reduced = $this->let->reduceToInterface();
		file_put_contents($this->interfacePath(), serialize($reduced));
		file_put_contents($this->interfacePath().".html", \Dump::let($reduced));
	}
	
	public function saveImportList()
	{
		file_put_contents($this->importListPath(), serialize($this->importList));
	}
}