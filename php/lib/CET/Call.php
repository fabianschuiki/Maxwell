<?php
namespace CET;

class Call extends Node
{
	public $func;
	public $operator;
	
	public function __construct(\LET\Call $node, array &$cet)
	{
		if ($node->func() instanceof \LET\BuiltinBinaryOp) {
			$this->operator = strval($node->func()->name());
		} else {
			$funcID = $node->func()->id;
			if (!isset($cet[$typeID])) \mwc\Compiler::error("unable to find function $funcID for {$node->desc()}");
			
			$this->func = $func= $cet[$funcID];
		}
	}
	
	public function details()
	{
		if ($this->func) return "{$this->func->name()}()";
		if ($this->operator) {
			return "{$this->operator}";
		}
	}
}