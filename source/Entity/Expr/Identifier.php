<?php
namespace Entity\Expr;
use Source\Range;

class Identifier extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Identifier $ident)
	{
		$e = new self;
		$e->generateID();
		$i = $ident->getIdent();
		$e->setRange($i->getRange());
		$e->setHumanRange($i->getRange());
		$e->setName($i->getText());
		return $e;
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
}