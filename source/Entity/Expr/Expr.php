<?php
namespace Entity\Expr;
use Entity\Entity;

abstract class Expr extends Entity
{
	public $analysis;
	
	public function __construct()
	{
		$this->analysis = \Analysis\Node\Node::makeForEntity($this);
	}
	
	static public function makeFromSyntaxNode(\AST\Expr\Expr $node)
	{
		if ($node instanceof \AST\Expr\Constant) return Constant::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\Identifier) return Identifier::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\VarDef) return VarDef::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\Operator\Binary) return Operator\Binary::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\MemberAccess) return MemberAccess::makeFromSyntaxNode($node);
		if ($node instanceof \AST\Expr\NewOp) return NewOp::makeFromSyntaxNode($node);
		throw new \exception("Unable to wrap ".vartype($node));
	}
}