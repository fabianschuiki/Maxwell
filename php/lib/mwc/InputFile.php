<?php
namespace mwc;

class InputFile extends SourceFile
{
	public $source;
	public $ast;
	public $let;
	
	public function load()
	{
		if ($this->source) return;
		
		$f= new \SourceFile;
		$f->path = $this->path;
		$f->load();
		$this->source = $f;
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
	
	public function analyze()
	{
		global $issues;
		assert($this->let instanceof \LET\Root);
		
		$analyzer = new \Analyzer;
		$analyzer->issues = $issues;
		$analyzer->root   = $this->let;
		$analyzer->run();
		if ($issues->dumpAndCheck()) return;
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
}