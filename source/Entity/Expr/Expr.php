<?php
namespace Entity\Expr;
use Entity\Entity;

class Expr extends Entity
{
	static public function makeFromSyntaxNode(\AST\Expr\Expr $node)
	{
		if ($node instanceof \AST\Expr\Constant) return Constant::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\Identifier) return Identifier::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\VarDef) return VarDef::makeFromSyntaxNode($node);
		throw new \exception("Unable to wrap ".vartype($node));
	}
}