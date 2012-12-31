<?php
namespace Entity\Stmt;
use Entity\Entity;

abstract class Stmt extends Entity
{
	static public function makeFromSyntaxNode(\AST\Stmt\Stmt $node)
	{
		if ($node instanceof \AST\Stmt\Expr) return Expr::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Stmt\IfStmt) return IfStmt::makeFromSyntaxNode($node);
		throw new \exception("Unable to wrap ".vartype($node));
	}
}