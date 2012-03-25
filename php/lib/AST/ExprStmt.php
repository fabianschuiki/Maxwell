<?php
namespace AST;

class ExprStmt extends Stmt
{
	public $expr;
	
	public function __construct(Expr $expr)
	{
		$this->expr = $expr;
	}
}
