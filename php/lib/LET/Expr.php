<?php
namespace LET;

abstract class Expr extends TypedNode
{
	///Returns a new subcalss of Expr wrapping the given expression.
	static public function make(Scope $scope, \AST\Expr $expr)
	{
		$classMapping = array(
			'Const' => 'Constant'
		);
		
		//Guess the class based on the expression kind.
		$kind  = preg_replace('/Expr$/', '', $expr->kind());
		if (isset($classMapping[$kind])) $kind = $classMapping[$kind];
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
	
	/*public function complainAboutAmbiguities()
	{
		global $issues;
		$type = $this->type();
		if (!$type) {
			$issues[] = new \Issue(
				'error',
				"Impossible to infer type of expression.",
				$this
			);
		} else if (!$type->isSpecific()) {
			$issues[] = new \Issue(
				'error',
				"Expression is of generic type '{$type->details()}' which cannot be compiled.",
				$this
			);
		} else {
			parent::complainAboutAmbiguities();
		}
	}*/
}