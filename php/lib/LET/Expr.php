<?php
namespace LET;

class Expr extends Node
{
	static public function make(Scope $scope, \AST\Expr $expr)
	{
		//Guess the class based on the expression kind.
		$kind  = preg_replace('/Expr$/', '', $expr->kind());
		$class = __NAMESPACE__.'\\'.$kind.'_AST';
		if (class_exists($class)) {
			return new $class($scope, $expr);
		} else {
			echo "class \033[1m$class\033[0m not found\n";
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