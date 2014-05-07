<?php
namespace CET;

class Call extends Node
{
	public $func;
	public $arguments;
	
	public function __construct(\LET\Call $node, array &$cet)
	{
		$funcID = $node->func()->id;
		if (!isset($cet[$funcID])) \mwc\Compiler::error("unable to find function $funcID for {$node->desc()}");
		$this->func = $cet[$funcID];
		
		$arguments = array();
		foreach ($node->args()->fields() as $name => $arg) $arguments[] = Node::make($arg, $cet);
		$this->arguments = $arguments;
	}
	
	public function details() { return "{$this->func->name()}()"; }
	
	public function generateCode(\C\Container $root)
	{
		$arguments = array_map(function($a) use ($root) { return $a->generateCode($root); }, $this->arguments);
		
		if ($this->func instanceof BuiltinOp) {
			if ($this->func->name() == 'new') {
				return new \C\Expr("mw_new(".$arguments[0]->getExpr().")");
			}
			return new \C\Operator($this->func->name(), $arguments);
		} else {
			$args = array_map(function($a) { return $a->getExpr(); }, $arguments);
			$node = new \C\Expr;
			$node->code = "{$this->func->name()}(".implode(', ', $args).")";
			return $node;
		}
	}
}