<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Source\Range;

class Identifier extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Identifier $ident)
	{
		$e = new self;
		$e->generateID();
		$i = $ident->getIdent();
		$e->setRange($i->getRange());
		$e->setName($i->getText());
		return $e;
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		$this->setScope($scope);
	}
	
	public function getChildEntities() { return array(); }
}