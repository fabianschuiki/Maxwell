<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Source\Range;

class NativeType extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\NativeType $expr)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($expr->getRange());
		$e->setName(implode(" ", array_map(function($t){return $t->getText();}, $expr->getTokens()->getTokens())));
		return $e;
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function getChildEntities() { return array(); }
}