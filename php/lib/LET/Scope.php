<?php
namespace LET;

class Scope
{
	public $outer;
	
	public $types = array();
	public $funcs = array();
	public $vars  = array();
	
	public function __construct($outer = null)
	{
		assert(!$outer || $outer instanceof Scope);
		$this->outer = $outer;
	}
	
	public function add($node)
	{
		if (!$node) return;
		assert($node instanceof Node);
		$node->scope = $this;
		
		//Add to node to the appropriate container.
		switch ($node->kind()) {
			case 'Type':     $this->types[] = $node; break;
			case 'Func':     $this->funcs[] = $node; break;
			case 'FuncArg':  $this->vars[]  = $node; break;
			case 'Variable': $this->vars[]  = $node; break;
			default: {
				trigger_error($node->kind()." not allowed in scope.");
			} break;
		}
	}
}