<?php
namespace AST\Stmt;
use Lexer\Token;

class Import extends Keyword
{
	protected $names;
	
	public function __construct(Token $keyword, array $names, Token $semicolon = null)
	{
		foreach ($names as $n) assert($n instanceof Token);
		$this->keyword = $keyword;
		$this->names = $names;
		$this->semicolon = $semicolon;
	}
	
	public function getNames() { return $this->names; }
}