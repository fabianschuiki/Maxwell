<?php
namespace CET;

class FuncArg extends Node
{
	public $name;
	public $type;
	
	public function __construct(\LET\FuncArg $node, array &$cet)
	{
		$this->name = $node->name();
	}
	
	public function name() { return $this->name; }
	public function details() { return $this->name(); }
	
	public function process(\LET\FuncArg $node, array &$cet)
	{
		$type = $node->type();
		
		if ($type instanceof \LET\PrimitiveBuiltinType) {
		} else {
			$typeID = $type->id;
			if (!isset($cet[$typeID])) \mwc\Compiler::error("no CET node found for type of function argument {$node->details()}");
			$this->type = $cet[$typeID];
		}
	}
	
	public function getType()
	{
		return $this->type->name();
	}
	
	public function getReference()
	{
		return new \C\Expr($this->name());
	}
	
	public function getDefinition()
	{
		return "{$this->getType()} {$this->name()}";
	}
}