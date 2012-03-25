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
		$node->scope = $this;
		
		//Add to node to the appropriate container.
		switch ($node->kind()) {
			case 'Type': $this->types[] = $node; break;
			case 'Func': $this->funcs[] = $node; break;
			default: {
				trigger_error($node->type()." not allowed in scope.");
			} break;
		}
	}
}