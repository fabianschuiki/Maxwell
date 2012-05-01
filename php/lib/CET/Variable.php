<?php
namespace CET;

class Variable extends Node
{
	public $name;
	public $type;
	public $initial;
	public $pointer;
	
	public function __construct(\LET\Variable $node, array &$cet)
	{
		parent::__construct();
		if ($node->type() instanceof \LET\NativeType) Node::make($node->type(), $cet);
		
		$typeID = $node->type()->id;
		if (!isset($cet[$typeID])) \mwc\Compiler::error("unable to find type $typeID for variable {$node->details()}");
		$type = $cet[$typeID];
		
		$initial = null;
		if ($node->initial) $initial = Node::make($node->initial, $cet);
		
		$this->name    = $node->name();
		$this->type    = $type;
		$this->initial = $initial;
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
		$def = "{$this->getType()} {$this->name()}";
		if ($this->initial)	$def .= " = ".$this->initial->generateCode($root)->getExpr();
		
		$root->add(new \C\Stmt($def));
		return null;
	}
	
	public function getReference()
	{
		return new \C\Expr($this->name());
	}
}