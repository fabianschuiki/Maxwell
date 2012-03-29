<?php
namespace LET;

abstract class Node
{
	public $scope;
	
	///Returns the type of this LET node, which is its class name without the LET namespace.
	public function kind()
	{
		$c = get_class($this);
		$s = strlen(__NAMESPACE__)+1;
		$e = strpos($c, '_');
		if ($e === false) $e = strlen($c);
		return substr($c, $s, $e-$s);
	}
	
	///Returns a description of this LET node.
	public function desc()
	{
		$str = $this->kind();
		if (method_exists($this, 'details')) {
			$str .= " {$this->details()}";
		}
		return $str;
	}
	abstract function details();
	
	/// Returns the human readable description of this node.
	public function nice() { return $this->kind(); }
	
	///Returns this node's subnodes.
	public function children()
	{
		$children = array();
		foreach ($this as $key => $value) {
			if ($value instanceof Node) $children[] = $value;
		}
		return $children;
	}
	
	///Returns whether the given node is a child node of this node.
	public function hasChild(Node $other)
	{
		//TODO: fix this $node->constraintTarget() thing so it becomes clear in the function name that the constraint target is checked, not the node itself.
		$children = array_filter(array_map(function($node){ return $node->constraintTarget(); }, $this->children()));
		if (in_array($other, $children, true)) return true;
		
		foreach ($children as $child) {
			if ($child->hasChild($other)) return true;
		}
		
		return false;
	}
	
	///Returns the range in the source file of this node.
	public function range()
	{
		$ranges = array();
		foreach ($this as $key => $value) {
			if ($value instanceof \AST\Node) $ranges[] = $value->range();
		}
		$ranges = array_filter($ranges);
		return \Range::union($ranges);
	}
	
	///Handles generic function calls.
	public function __call($name, array $args)
	{
		foreach ($this->children() as $child) {
			call_user_func_array(array($child, $name), $args);
		}
	}
	
	///The default implementation simply calls reduce() on all children() and returns the node itself. 
	public function reduce()
	{
		$this->__call('reduce', func_get_args());
		return $this;
	}
	
	public function spawnConstraints(array &$cons) { foreach ($this->children() as $node) $node->spawnConstraints($cons); }
	public function constraintTarget() { return $this; }
}