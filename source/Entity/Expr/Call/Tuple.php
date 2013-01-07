<?php
namespace Entity\Expr\Call;
use Entity\Expr\Expr;

class Tuple extends Expr
{
	static public function makeFromSyntaxNodes(array $nodes, \Source\Range $range)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($range);
		
		$args = array();
		foreach ($nodes as $node) {
			$args[] = Argument::makeFromSyntaxNode($node);
		}
		$e->setArgs($args);
		
		return $e;
	}
	
	protected $args;
	
	public function setArgs(array $a) { $this->args = $a; foreach($a as $arg) $arg->setParent($this); }
	public function getArgs() { return $this->args; }
	
	public function initScope(\Entity\Scope\Scope &$scope)
	{
		foreach ($this->args as $arg) {
			$arg->initScope($scope);
		}
	}
	
	public function getChildEntities() { return $this->args; }
}