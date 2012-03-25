<?php
namespace AST;

class BinaryOpExpr extends Expr
{
	public $op;
	public $expr;
	
	public function __construct(\Token $op, Expr $expr)
	{
		assert($op->is('symbol'));
		$this->op  = $op;
		$this->expr = $expr;
	}
}