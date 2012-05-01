<?php
namespace CET;

class Type extends Node
{
	public $name;
	public $members;
	public $record;
	
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
	public function recordName() { return "{$this->name}_type"; }
	
	public function details() { return "{$this->name()}"; }
	
	public function process(\LET\ConcreteType $node, array &$cet)
	{
		foreach ($node->members() as $member) {
			$m = $cet[$member->id];
			$m->process($member, $cet);
		}
		$this->record = new TypeRecord($this);
	}
	
	public function generateCode(\C\Container $root)
	{
		$this->record->generateCode($root);
		
		//Generate the type definition.
		$node = new \C\TypeDef;
		$node->name = $this->name();
		$node->fields[] = new \C\Stmt("{$this->record->getType()} * isa");
		foreach ($this->members as $member) {
			$node->fields[] = new \C\Stmt("int {$member->name()}");
		}
		$root->add($node);
	}
	
	public function getReference()
	{
		return new \C\Expr("&{$this->recordName()}");
	}
}