<?php
namespace AST;

class ExprStmt extends Stmt
{
	public $expr;
	
	public function __construct(Expr $expr)
	{
		$this->expr = $expr;
	}
	
	public function nice()
	{
		if ($this->expr) return $this->expr->nice().' statement';
		return parent::nice();
	}
}
