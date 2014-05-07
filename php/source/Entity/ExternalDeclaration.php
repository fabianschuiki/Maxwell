<?php
namespace Entity;
use Source\Range;

class ExternalDeclaration extends RootEntity
{
	static public function makeFromSyntaxNode(\AST\Stmt\External $ext)
	{
		$e = new self;
		$e->generateID();
		$e->pushID();
		$e->setRange(Range::union($ext->getKeyword()->getRange(), $ext->getGroup()->getRange()));
		$e->setHumanRange(Range::union($ext->getKeyword()->getRange(), $ext->getName()->getRange()));
		$e->setName($ext->getName()->getText());
		
		$decls = array();
		foreach ($ext->getDeclarations() as $d) {
			if ($d instanceof \AST\Stmt\FuncDef) $decls[] = FunctionDefinition::makeFromSyntaxNode($d);
		}
		$e->setDeclarations($decls);
		
		$e->popID();
		return $e;
	}
	
	protected $name;
	protected $declarations;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setDeclarations(array $d) { $this->declarations = $d; }
	public function getDeclarations() { return $this->declarations; }
	
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
		foreach ($this->declarations as $decl) {
			$decl->initScope($s);
		}
	}
	
	public function getChildEntities()
	{
		return $this->declarations;
	}
}