<?php
namespace Interpreter;

class Interpreter
{
	public $root;
	
	public function evaluate(\LET\Expr $node)
	{
		echo "evaluating {$node->desc()}\n";
	}
}