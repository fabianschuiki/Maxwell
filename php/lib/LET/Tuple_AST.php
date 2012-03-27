<?php
namespace LET;

class Tuple_AST extends Expr
{
	public $asn;
	public $exprs;
	
	public function __construct(Scope $scope, \AST\TupleExpr $node)
	{
		$exprs = array();
		foreach ($node->exprs as $expr) {
			$exprs[] = Expr::make($scope, $expr);
		}
		$exprs = array_filter($exprs);
		
		$this->asn   = $node;
		$this->exprs = $exprs;
		$this->scope = $scope;
	}
	
	public function children() { return $this->exprs; }
	
	public function details()
	{
		$exprs = array_map(function($expr){ return $expr->details(); }, $this->exprs);
		$exprs = implode(', ', $exprs);
		
		return "($exprs)";
	}
}