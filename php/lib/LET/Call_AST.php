<?php
namespace LET;

class Call_AST extends Call
{
	public $asn;
	public $callee;
	public $args;
	
	public function __construct(Scope $scope, \AST\CallExpr $node)
	{
		/*$args = array();
		foreach ($node->args as $arg) {
			$args[] = new CallArg_AST($scope, $arg);
		}
		$args = array_filter($args);*/
		
		//DEBUG: create a tuple from the arguments.
		$args = array();
		foreach ($node->args as $arg) {
			$name = $arg->name->text;
			$expr = Expr::make($scope, $arg->expr);
			if (!$expr) continue;
			if ($name) {
				$args[$name] = $expr;
			} else {
				$args[] = $expr;
			}
		}
		
		$this->asn    = $node;
		$this->callee = Expr::make($scope, $node->callee);
		$this->args   = new Tuple_Impl($scope, $args);
		$this->scope  = $scope;
	}
	
	public function callee() { return $this->callee; }
	public function args()   { return $this->args; }
}