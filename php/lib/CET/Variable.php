<?php
namespace CET;

class Variable extends Node
{
	public $name;
	public $type;
	
	public function __construct(\LET\Variable $node, array &$cet)
	{
		$typeID = $node->type()->id;
		if (!isset($cet[$typeID])) \mwc\Compiler::error("no CET node found for type of variable {$node->details()}");
		$type = $cet[$typeID];
		
		$this->name = $node->name();
		$this->type = $type;
	}
	
	public function name() { return $this->name; }
	
	public function details() { return "{$this->type->name()} {$this->name()}"; }
}