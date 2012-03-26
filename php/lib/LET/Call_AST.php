<?php
namespace LET;

class Call_AST extends Call
{
	public $asn;
	public $callee;
	public $args;
	
	public function __construct(Scope $scope, \AST\CallExpr $expr)
	{
		$args = array();
		foreach ($expr->args as $arg) {
			$args[] = new CallArg_AST($scope, $arg);
		}
		$args = array_filter($args);
		
		$this->asn    = $expr;
		$this->callee = Expr::make($scope, $expr->callee);
		$this->args   = $args;
		$this->scope  = $scope;
	}
	
	public function callee() { return $this->callee; }
	public function args()   { return $this->args; }
}