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
}