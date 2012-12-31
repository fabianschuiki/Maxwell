<?php
namespace CET;

class NativeFunc extends Node
{
	public $name;
	
	public function __construct(\LET\NativeFunc_AST $node, array &$cet)
	{
		parent::__construct();
		
		$map  = function($a) use (&$cet) { return $cet[$a->id] = Node::make($a, $cet); };
		$ins  = array_map($map, $node->inputs());
		$outs = array_map($map, $node->outputs());
		
		$this->name  = strval($node->name());
		$this->stmts = array();
	}
	
	public function name()    { return $this->name; }
	public function details() { return $this->name(); }
	
	public function process(\LET\Func $node, array &$cet)
	{
		foreach ($node->inputs()  as $in)  { $a = $cet[$in ->id]; $a->process($in,  $cet); $a->func = $this; }
		foreach ($node->outputs() as $out) { $a = $cet[$out->id]; $a->process($out, $cet); $a->func = $this; }
	}
	
	public function generateCode(\C\Container $root) { return null; }
}