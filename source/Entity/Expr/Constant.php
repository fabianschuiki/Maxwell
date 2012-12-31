<?php
namespace Entity\Expr;
use Source\Range;
use Entity\Scope\Scope;

class Constant extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Constant $const)
	{
		$e = new self;
		$e->generateID();
		
		$v = $const->getValue();
		
		$e->setRange($v->getRange());
		$e->setType($v->getType());
		$e->setValue($v->getText());
		return $e;
	}
	
	protected $type;
	protected $value;
	
	public function setType($t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	public function setValue($v) { $this->value = $v; }
	public function getValue() { return $this->value; }
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		$this->setScope($scope);
	}
	
	public function getChildEntities() { return array(); }
}