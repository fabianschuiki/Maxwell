<?php
namespace Entity;
use Source\Range;
use Entity\Scope\Scope;

class FunctionDefinition extends RootEntity
{
	static public function makeFromSyntaxNode(\AST\Stmt\FuncDef $def)
	{
		$e = new self;
		$e->generateID();
		$e->pushID();
		$e->setRange(Range::union($def->getKeyword()->getRange(), $def->getBody()->getRange()));
		$e->setHumanRange(Range::union($def->getKeyword()->getRange(), $def->getName()->getRange()));
		$e->setName($def->getName()->getText());
		$e->setBody(Block::makeFromSyntaxNode($def->getBody()));
		$e->popID();
		return $e;
	}
	
	protected $name;
	protected $body;
	protected $scope;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setBody(Block $b) { $this->body = $b; }
	public function getBody() { return $this->body; }
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope()
	{
		$scope = new Scope;
		$scope->generateID();
		$this->setScope($scope);
		$this->body->initScope($scope);
	}
}