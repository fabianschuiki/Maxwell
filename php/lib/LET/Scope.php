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
		if ($node instanceof ConcreteType) $this->types[] = $node; else
		if ($node instanceof Func)         $this->funcs[] = $node; else
		if ($node instanceof FuncArg)      $this->vars[]  = $node; else
		if ($node instanceof Variable)     $this->vars[]  = $node;
		else {
			trigger_error($node->kind()." not allowed in scope.");
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
	
	public function spawnConstraints()
	{
		$constraints = array();
		foreach ($this->children() as $node) {
			$node->spawnConstraints($constraints);
		}
		
		$reduced = array();
		foreach ($constraints as $a) {
			$kind = $a->kind();
			$merged = false;
			foreach ($reduced as $b) {
				if ($kind != $b->kind()) continue;
				if ($b->merge($a)) {
					$merged = true;
					break;
				}
			}
			if (!$merged) $reduced[] = $a;
		}
		
		return array_filter($reduced, function($constraint){ return !$constraint->met(); });
	}
}