<?php
namespace LET;

class Call_AST extends Call
{
	public $asn;
	public $callee;
	public $args;
	
	public function __construct(Scope $scope, \AST\CallExpr $node)
	{
		$args = array();
		$callee = Expr::make($scope, $node->callee);
		if ($callee instanceof Member) {
			$args["this"] = $callee->expr();
			$callee = new Ident_Impl($scope, $callee->name());
		}
		
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
		$args = new Tuple_Impl($scope, $args);
		$args->parent = $this;
		
		$this->asn    = $node;
		$this->callee = $callee;
		$this->args   = $args;
		$this->scope  = $scope;
	}
	
	public function callee() { return $this->callee; }
	public function args()   { return $this->args; }
}