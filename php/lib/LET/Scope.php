<?php
namespace LET;

class Scope
{
	public $node;
	public $outer;
	
	public $types = array();
	public $funcs = array();
	public $vars  = array();
	
	public function __construct($outer = null, $node = null)
	{
		assert(!$outer || $outer instanceof Scope);
		assert(!$node  || $node  instanceof Node);
		$this->outer = $outer;
		$this->node  = $node;
	}
	
	public function add($node)
	{
		if (!$node) return;
		assert($node instanceof Node);
		$node->scope = $this;
		
		//Add to node to the appropriate container.
		switch ($node->kind()) {
			case 'ConcreteType': $this->types[] = $node; break;
			case 'Func':         $this->funcs[] = $node; break;
			case 'FuncArg':      $this->vars[]  = $node; break;
			case 'Variable':     $this->vars[]  = $node; break;
			default: {
				trigger_error($node->kind()." not allowed in scope.");
			} break;
		}
	}
	
	public function children()
	{
		return array_merge($this->types, $this->funcs);
	}
	
	public function __call($name, array $args)
	{
		foreach ($this->children() as $node) {
			call_user_func_array(array($node, $name), $args);
		}
	}
	
	///Searches the scope hierarchy (this and its parents) for nodes with the given name.
	public function find($name, $noVars = false)
	{
		if (!$name) return array();
		assert(is_string($name));
		
		$filter = function($node) use ($name) { return ($node->name() == $name); };
		
		$vars = array();
		if (!$noVars) {
			$vars = array_filter($this->vars, $filter);
		}
		
		$outer = array();
		if ($this->outer) {
			$outer = $this->outer->find($name, $noVars || count($vars));
		}
		
		$nodes = array_merge(
			array_filter($this->types, $filter),
			array_filter($this->funcs, $filter),
			$vars,
			$outer
		);
		
		return $nodes;
	}
}