<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Source\Range;

class Call extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Call $call)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($call->getRange());
		$e->setCallee(Call\Callee::makeFromSyntaxNode($call->getCallee()));
		$e->setArgs(Call\Tuple::makeFromSyntaxNodes($call->getArgs()));
		return $e;
	}
	
	protected $callee;
	protected $args;
	
	public function setCallee(Call\Callee $c) { $this->callee = $c; $c->setParent($this); }
	public function getCallee() { return $this->callee; }
	
	public function setArgs(Call\Tuple $a) { $this->args = $a; $a->setParent($this); }
	public function getArgs() { return $this->args; }
	
	
	public function initScope(Scope &$scope)
	{
		$this->callee->initScope($scope);
		$this->args->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->callee, $this->args); }
}