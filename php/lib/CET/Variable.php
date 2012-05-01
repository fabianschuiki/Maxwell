<?php
namespace CET;

class Variable extends Node
{
	public $name;
	public $type;
	public $pointer;
	
	public function __construct(\LET\Variable $node, array &$cet)
	{
		parent::__construct();
		if ($node->type() instanceof \LET\NativeType) Node::make($node->type(), $cet);
		
		$typeID = $node->type()->id;
		if (!isset($cet[$typeID])) \mwc\Compiler::error("unable to find type $typeID for variable {$node->details()}");
		$type = $cet[$typeID];
		
		$this->name    = $node->name();
		$this->type    = $type;
		$this->pointer = !$node->type()->keepOnStack();
	}
	
	public function name() { return $this->name; }
	public function isPointer() { return $this->pointer; }
	
	public function details() { return "{$this->getType()} {$this->name()}"; }
	
	public function getType()
	{
		$t = $this->type->name();
		if ($this->pointer) $t .= " *";
		return $t;
	}
	
	public function generateCode(\C\Container $root)
	{
		$root->add(new \C\Stmt("{$this->getType()} {$this->name()}"));
		return null;
	}
	
	public function getReference()
	{
		return new \C\Expr($this->name());
	}
}