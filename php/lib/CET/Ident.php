<?php
namespace CET;

class Ident extends Node
{
	public $target;
	
	public function __construct(\LET\Ident $node, array &$cet)
	{
		$targetID = $node->boundTo->id;
		if (!isset($cet[$targetID])) \mwc\Compiler::error("no CET node $targetID found for {$node->desc()}");
		$this->target = $cet[$targetID];
	}
	
	public function details() { return "@{$this->target->name()}"; }
	
	public function generateCode(\C\Container $root)
	{
		/*if ($this->target instanceof Type) return new \C\Expr($this->target->name());
		\mwc\Compiler::error("unable to generate code for {$this->target->desc()}");*/
		return $this->target->getReference();
	}
}