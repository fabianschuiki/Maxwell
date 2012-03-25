<?php
namespace LET;

class Scope
{
	public $issues;
	
	public $types = array();
	public $funcs = array();
	
	public function add($node)
	{
		if (!$node) return;
		assert($node instanceof Node);
		
		//Add to node to the appropriate container.
		switch ($node->type()) {
			case 'Type': $types[] = $node; break;
			case 'Func': $funcs[] = $node; break;
			default: {
				trigger_error($node->type()." not allowed in scope.");
			} break;
		}
		
		echo "adding: {$node->desc()}\n";
	}
}