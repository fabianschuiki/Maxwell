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
		$e->setCallee(Expr::makeFromSyntaxNode($call->getCallee()));
		$e->setArgs(Call\Tuple::makeFromSyntaxNodes($call->getArgs()));
		return $e;
	}
	
	protected $callee;
	protected $args;
	
	public function setCallee(Expr $c) { $this->callee = $c; }
	public function getCallee() { return $this->callee; }
	
	public function setArgs(Call\Tuple $a) { $this->args = $a; }
	public function getArgs() { return $this->args; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		$this->setScope($scope);
	}
	
	public function getChildEntities() { return array($callee, $args); }
}