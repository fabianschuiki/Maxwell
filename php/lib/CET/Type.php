<?php
namespace CET;

class Type extends Node
{
	public $name;
	
	public function __construct(\LET\ConcreteType $node, array &$cet)
	{
		parent::__construct();
		$this->name = strval($node->name());
		foreach ($node->members() as $member) Node::make($member, $cet);
	}
	
	public function name() { return "{$this->name}_t"; }
	
	public function details() { return "{$this->name()}"; }
	
	public function process(\LET\ConcreteType $node, array &$cet)
	{
	}
	
	public function generateCode(\C\Container $root)
	{
		
	}
}