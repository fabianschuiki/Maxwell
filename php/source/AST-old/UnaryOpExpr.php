<?php
namespace AST;

class UnaryOpExpr extends Expr
{
	public $op;
	public $expr;
	
	public function __construct(\Token $op, Expr $expr)
	{
		assert($op->is('symbol') || $op->is('identifier'));
		$this->op  = $op;
		$this->expr = $expr;
	}
}