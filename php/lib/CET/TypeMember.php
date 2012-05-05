<?php
namespace CET;

class TypeMember extends Node
{
	public $name;
	public $type;
	public $pointer;
	
	public function __construct(\LET\TypeMember_AST $node, array &$cet)
	{
		parent::__construct();
		$this->name    = $node->name();
		$this->pointer = !$node->type()->keepOnStack();
	}
	
	public function name() { return $this->name; }
	public function type() { return $this->type; }
	
	public function isPointer() { return $this->pointer; }
	public function details() { return $this->name(); }
	
	public function process(\LET\TypeMember $node, array &$cet)
	{
		if ($node->type() instanceof \LET\NativeType) Node::make($node->type(), $cet);
		
		$typeID = $node->type()->id;
		if (!isset($cet[$typeID])) \mwc\Compiler::error("no type node $typeID found for member {$node->details()}");
		$this->type = $cet[$typeID];
	}
	
	public function getType()
	{
		$t = $this->type->name();
		if ($this->pointer) $t .= " *";
		return $t;
	}
}