<?php
namespace LET;

class Expr extends Node
{
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
}