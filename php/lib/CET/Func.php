<?php
namespace CET;

class Func extends Node
{
	public $name;
	
	public function __construct(\LET\Func $node, array &$cet)
	{
		parent::__construct();
		$this->name = strval($node->name());
	}
	
	public function name() { return $this->name; }
	
	public function details() { return "{$this->name()}"; }
	
	public function process(\LET\Func $node, array &$cet)
	{
		foreach ($node->stmts() as $stmt) $cet[$stmt->id] = Node::make($stmt, $cet);
	}
}