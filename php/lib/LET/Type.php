<?php
namespace LET;

abstract class Type extends Node
{
	/** If $expr is null, returns a GenericType. If $expr is either an AST\Expr or Expr, returns a TypeExpr. Otherwise returns null. */
	static public function make(Scope $scope, $expr)
	{
		if ($expr) {
			if ($expr instanceof \AST\Expr) {
				$expr = Expr::make($scope, $expr);
			}
			if ($expr instanceof Expr) {
				return new TypeExpr($scope, $expr);
			}
		} else {
			return new GenericType($scope);
		}
		return null;
	}
	
	public function isSpecific() { return false; }
}