<?php
namespace AST;

class CallExpr extends Expr
{
	public $callee;
	public $args;
	
	public function __construct(Expr $callee, array $args)
	{
		$this->callee = $callee;
		$this->args   = $args;
	}
	
	public function nice() { return "Function call"; }
}