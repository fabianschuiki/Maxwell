<?php
namespace LET;

abstract class Expr extends Node
{
	///Returns a new subcalss of Expr wrapping the given expression.
	static public function make(Scope $scope, \AST\Expr $expr)
	{
		//Guess the class based on the expression kind.
		$kind  = preg_replace('/Expr$/', '', $expr->kind());
		if ($kind == 'Const') $kind = 'Constant';
		$class = __NAMESPACE__.'\\'.$kind.'_AST';
		if (class_exists($class)) {
			return new $class($scope, $expr);
		}
		
		//No class found.
		global $issues;
		$issues[] = new \Issue(
			'error',
			"{$expr->nice()} is not allowed in an expression.",
			$expr
		);
		return null;
	}
	
	///Returns the inferred type of this node.
	public function infType() { return null; }
}