<?php
namespace CET;

class BuiltinOp extends Node
{
	public $name;
	
	public function __construct(\LET\Func $node, array &$cet)
	{
		$this->name = $node->name();
	}
	
	public function name() { return $this->name; }
	public function details() { return $this->name(); }
}