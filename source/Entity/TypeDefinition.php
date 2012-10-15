<?php
namespace Entity;
use Source\Range;
use Lexer\Token;

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
	
	public function setScope(Scope\Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope\Scope $scope = null)
	{
		if ($scope) {
			$s = new Scope\ScopeDeclaration;
			$s->setUpper($scope);
			$s->setDeclares($this);
		} else {
			$s = new Scope\ScopeRoot;
			$s->setRootEntity($this);
		}
		$s->generateID();
		$this->setScope($s);
	}
	
	public function getChildEntities()
	{
		return array();
	}
}