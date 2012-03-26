<?php
namespace LET;

class Expr extends Node
{
	static public function make(Scope $scope, \AST\Expr $expr)
	{
		switch ($expr->kind()) {
			case 'CallExpr':     return new Call_AST ($scope, $expr); break;
			case 'IdentExpr':    return new Ident_AST($scope, $expr); break;
			case 'BinaryOpExpr': return new BinaryOp ($scope, $expr); break;
			default: {
				global $issues;
				$issues[] = new \Issue(
					'error',
					"{$expr->nice()} is not allowed in an expression.",
					$expr
				);
			} break;
		}
		return null;
	}
}