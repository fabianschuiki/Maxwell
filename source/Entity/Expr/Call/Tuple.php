<?php
namespace Entity\Expr\Call;
use Entity\Expr\Expr;

class Tuple extends Expr
{
	static public function makeFromSyntaxNodes(array $nodes)
	{
		$e = new self;
		$e->generateID();
		
		if (count($nodes)) {
			$e->setRange(\Source\Range::union(array_map(function($n){ return $n->getRange(); }, $nodes)));
		}
		
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