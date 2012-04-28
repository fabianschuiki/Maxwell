<?php
namespace CET;

class TypeMember extends Node
{
	public $name;
	public $type;
	
	public function __construct(\LET\TypeMember_AST $node, array &$cet)
	{
		parent::__construct();
		
		/*$typeID = $node->type()->id;
		if (!isset($cet[$typeID])) \mwc\Compiler::error("no CET node found for type of member {$node->details()}");
		$type = $cet[$typeID];*/
		
		$this->name = $node->name();
		$this->type = $type;
	}
	
	public function name() { return $this->name; }
	public function type() { return $this->type; }
	
	public function details() { return $this->name(); }
}