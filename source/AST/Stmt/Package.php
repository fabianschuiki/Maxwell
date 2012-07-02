<?php
namespace AST\Stmt;
use Lexer\Token;

class Package extends Stmt
{
	protected $name;
	
	public function __construct(Token $keyword, Token $name, Token $semicolon = null)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->name = $name;
		$this->semicolon = $semicolon;
	}
	
	public function getName() { return $this->name; }
}