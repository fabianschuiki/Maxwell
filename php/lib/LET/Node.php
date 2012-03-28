<?php
namespace LET;

abstract class Node
{
	public $scope;
	public $constraints;
	public $typeConstraint;
	
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
		$children = array_map(function($node){ return $node->constraintTarget(); }, $this->children());
		if (in_array($other, $children, true)) return true;
		
		foreach ($children as $child) {
			if ($child->hasChild($other)) return true;
		}
		
		return false;
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
	
	public function clearConstraints()
	{
		$this->__call('clearConstraints', array());
		$this->constraints = array();
		$this->typeConstraint = new GenericType;
	}
	public function imposeConstraint(Constraint $constraint)
	{
		echo "\033[1mimpose constraint\033[0m {$constraint->type->details()} \033[1mon\033[0m {$this->details()}\n";
		//letDumpNPause();
		$this->constraints[] = $constraint;
		if ($this->typeConstraint) $this->typeConstraint = Type::intersect($this->typeConstraint, $constraint->type());
	}
	public function resolveConstraints()
	{
		$this->__call('resolveConstraints', array());
		//$type = new GenericType;
		$constraints = $this->constraints;
		if (!$constraints) return;
		while (count($constraints) > 0) {
			$a = array_shift($constraints);
			foreach ($constraints as $b) {
				if (!Type::intersect($a->type(), $b->type())) {
					global $issues;
					$issues[] = new Issue(
						'error',
						"{$this->desc()}: {$a->desc()} and {$b->desc()} cannot both be met."
					);
				}
			}
			//$type = Type::intersect($type, $a->type());
		}
		//$this->typeConstraint = $type;
	}
}