<?php
namespace AST\Stmt;
use Lexer\Token;

class Expr extends Stmt
{
	protected $expr;
	
	public function __construct(\AST\Expr\Expr $expr, Token $semicolon = null)
	{
		parent::__construct();
		$this->expr = $expr;
		$this->semicolon = $semicolon;
	}
	
	public function getExpr() { return $this->expr; }
}