<?php
namespace CET;

class FuncArg extends Node
{
	public $name;
	public $type;
	public $func;
	
	public function __construct(\LET\FuncArg $node, array &$cet)
	{
		parent::__construct();
		$this->name = $node->name();
	}
	
	public function name() { return $this->name; }
	public function details() { return $this->name(); }
	
	public function process(\LET\FuncArg $node, array &$cet)
	{
		if ($node->type() instanceof \LET\NativeType) Node::make($node->type(), $cet);
		
		$typeID = $node->type()->id;
		if (!isset($cet[$typeID])) \mwc\Compiler::error("no CET node found for type of function argument {$node->details()}");
		$this->type = $cet[$typeID];
	}
	
	public function getType()
	{
		return $this->type->name();
	}
	
	public function getReference()
	{
		return $this->func->getArgReference($this);
	}
	
	public function getDefinition()
	{
		return "{$this->getType()} {$this->name()}";
	}
}