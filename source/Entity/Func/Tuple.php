<?php
namespace Entity\Func;
use Entity\Entity;

class Tuple extends Entity
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
	
	public function setArgs(array $a) { $this->args = $a; }
	public function getArgs() { return $this->args; }
	
	public function getChildEntities() { return $this->args; }
}