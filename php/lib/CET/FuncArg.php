<?php
namespace CET;

class FuncArg extends Node
{
	public $name;
	
	public function __construct(\LET\FuncArg $node, array &$cet)
	{
		$this->name = $node->name();
	}
	
	public function name() { return $this->name; }
	public function details() { return $this->name(); }
	
	public function getType()
	{
		return "void *";
	}
	
	public function getReference()
	{
		return new \C\Expr($this->name());
	}
	
	public function getDefinition()
	{
		return "{$this->getType()} {$this->name()}";
	}
}