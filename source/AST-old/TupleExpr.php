<?php
namespace AST;

class TupleExpr extends Expr
{
	public $exprs;
	
	public function __construct(array $exprs)
	{
		$this->exprs = $exprs;
	}
	
	public function range()
	{
		return \Range::union(array_map(function($expr){ return $expr->range(); }, $this->exprs));
	}
}