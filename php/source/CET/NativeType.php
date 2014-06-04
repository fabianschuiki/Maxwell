<?php
namespace CET;

class NativeType extends Node
{
	public $name;
	
	public function __construct(\LET\NativeType $node, array &$cet)
	{
		$this->name = $node->name();
	}
	
	public function name() { return $this->name; }
	public function details() { return "'{$this->name()}'"; }
}