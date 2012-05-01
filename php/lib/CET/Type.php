<?php
namespace CET;

class Type extends Node
{
	public $name;
	public $members;
	
	public function __construct(\LET\ConcreteType $node, array &$cet)
	{
		parent::__construct();
		$this->name = strval($node->name());
		
		$membersToProcess = array();
		$type = $node;
		while ($type) {
			$membersToProcess = array_merge($type->members(), $membersToProcess);
			$type = $type->parent;
		}
		
		$members = array();
		foreach ($membersToProcess as $member) $members[] = Node::make($member, $cet);
		
		$this->members = $members;
	}
	
	public function name() { return "{$this->name}_t"; }
	
	public function details() { return "{$this->name()}"; }
	
	public function process(\LET\ConcreteType $node, array &$cet)
	{
		foreach ($node->members() as $member) {
			$m = $cet[$member->id];
			$m->process($member, $cet);
		}
	}
	
	public function generateCode(\C\Container $root)
	{
		$node = new \C\TypeDef;
		$node->name = $this->name();
		$node->fields[] = new \C\Stmt("void * isa");
		foreach ($this->members as $member) {
			$node->fields[] = new \C\Stmt("int {$member->name()}");
		}
		$root->add($node);
	}
}