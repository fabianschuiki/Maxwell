<?php
namespace CET;

class Call extends Node
{
	public $func;
	public $arguments;
	public $operator;
	
	public function __construct(\LET\Call $node, array &$cet)
	{
		if ($node->func() instanceof \LET\BuiltinBinaryOp) {
			$this->operator = strval($node->func()->name());
		} else {
			$funcID = $node->func()->id;
			if (!isset($cet[$typeID])) \mwc\Compiler::error("unable to find function $funcID for {$node->desc()}");
			
			$this->func = $cet[$funcID];
		}
		
		$arguments = array();
		foreach ($node->args()->fields() as $name => $arg) $arguments[] = Node::make($arg, $cet);
		$this->arguments = $arguments;
	}
	
	public function details()
	{
		if ($this->func) return "{$this->func->name()}()";
		if ($this->operator) {
			return "{$this->operator}";
		}
	}
	
	public function generateCode(\C\Container $root)
	{
		$arguments = array_map(function($a) use ($root) { return $a->generateCode($root); }, $this->arguments);
		
		$node = new \C\Expr;
		if ($this->func) {
			$node->code = "{$this->func->name()}()";
		}
		if ($this->operator) {
			/*$node->code = "({$arguments[0]->getExpr()}) {$this->operator} ({$arguments[1]->getExpr()})";*/
			return new \C\Operator($this->operator, $arguments[0], $arguments[1]);
		}
		//$root->add($node);
		return $node;
	}
}