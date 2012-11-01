<?php
namespace AST\Stmt;
use Lexer\Token;

class External extends Keyword
{
	protected $name;
	protected $declarations;
	
	public function __construct(Token $keyword, Token $name, array $declarations, Token $semicolon = null)
	{
		parent::__construct();
		foreach ($declarations as $d) assert($d instanceof Stmt);
		$this->keyword = $keyword;
		$this->name = $name;
		$this->declarations = $declarations;
		$this->semicolon = $semicolon;
	}
	
	public function getName() { return $this->name; }
	public function getDeclarations() { return $this->declarations; }
}