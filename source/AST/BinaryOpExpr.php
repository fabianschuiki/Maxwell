<?php
namespace AST;

class BinaryOpExpr extends Expr
{
	public $op;
	public $lhs;
	public $rhs;
	
	public function __construct(\Token $op, Expr $lhs, Expr $rhs)
	{
		assert($op->is('symbol'));
		$this->op  = $op;
		$this->lhs = $lhs;
		$this->rhs = $rhs;
	}
}