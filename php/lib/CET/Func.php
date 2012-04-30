<?php
namespace CET;

class Func extends Node
{
	public $name;
	public $ins;
	public $outs;
	public $stmts;
	
	public function __construct(\LET\Func $node, array &$cet)
	{
		parent::__construct();
		
		$map  = function($a) use (&$cet) { return $cet[$a->id] = Node::make($a, $cet); };
		$ins  = array_map($map, $node->inputs());
		$outs = array_map($map, $node->outputs());
		
		$this->name  = strval($node->name());
		$this->ins   = $ins;
		$this->outs  = $outs;
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
	
	public function getReturnType()
	{
		if (count($this->outs) == 0) return 'void';
		if (count($this->outs) == 1) return $this->outs[0]->getType();
		return "{$this->name()}_ret";
	}
	
	public function generateCode(\C\Container $root)
	{
		$args = array_map(function($i) { return $i->getDefinition(); }, $this->ins);
		
		$node = new \C\Func;
		$node->signature = "{$this->getReturnType()} {$this->name()}(".implode(", ", $args).")";
		foreach ($this->stmts as $stmt) {
			$s = $stmt->generateCode($node->body);
			if ($s)	$node->body->add($s);
		}
		$root->add($node);
		return null;
	}
}