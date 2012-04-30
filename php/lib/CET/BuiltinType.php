<?php
namespace CET;

class BuiltinType extends Node
{
	public $name;
	
	public function __construct(\LET\BuiltinType $node, array &$cet)
	{
		$this->name = $node->name();
	}
	
	public function name() { return $this->name; }
	public function details() { return $this->name(); }
}