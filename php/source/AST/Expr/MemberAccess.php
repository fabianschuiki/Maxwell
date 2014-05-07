<?php
namespace AST\Expr;
use Lexer\Token;

class MemberAccess extends Expr
{
	protected $expr;
	protected $name;
	
	public function __construct(Expr $expr, Token $name)
	{
		parent::__construct();
		$this->expr = $expr;
		$this->name = $name;
	}
	
	public function getExpr() { return $this->expr; }
	public function getName() { return $this->name; }
}