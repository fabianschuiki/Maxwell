<?php
namespace CET;

class Func extends Node
{
	public $name;
	public $stmts;
	
	public function __construct(\LET\Func $node, array &$cet)
	{
		parent::__construct();
		$this->name = strval($node->name());
		$this->stmts = array();
	}
	
	public function name() { return $this->name; }
	
	public function details() { return "{$this->name()}"; }
	
	public function process(\LET\Func $node, array &$cet)
	{
		foreach ($node->stmts() as $stmt) {
			$s = Node::make($stmt, $cet);
			$this->stmts[] = $s;
			$cet[$stmt->id] = $s;
		}
	}
	
	public function generateCode(\C\Container $root)
	{
		$node = new \C\Func;
		$node->signature = "void {$this->name()}()";
		foreach ($this->stmts as $stmt) {
			$s = $stmt->generateCode($node->body);
			if ($s)	$node->body->add($s);
		}
		$root->add($node);
		return null;
	}
}