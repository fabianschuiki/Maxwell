<?php
namespace Entity;
use Source\Range;
use Lexer\Token;
use Entity\Scope\Scope;

class TypeDefinition extends RootEntity
{
	static public function makeFromSyntaxNode(\AST\Stmt\TypeDef $def)
	{
		$e = new self;
		$e->generateID();
		$e->pushID();
		$e->setRange(Range::union($def->getKeyword()->getRange(), $def->getBody()->getRange()));
		
		if ($def->getSuperType())
			$hr = $def->getSuperType();
		else
			$hr = $def->getName();
		$e->setHumanRange(Range::union($def->getKeyword()->getRange(), $hr->getRange()));
		
		$e->setName($def->getName()->getText());
		if ($def->getSuperType())
			$e->setSuperType($def->getSuperType()->getText());
		
		$e->popID();
		return $e;
	}
	
	protected $name;
	protected $superType;
	protected $scope;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setSuperType($s) { $this->superType = $s; }
	public function getSuperType() { return $this->superType; }
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope()
	{
		$scope = new Scope;
		$scope->generateID();
		$this->setScope($scope);
	}
}