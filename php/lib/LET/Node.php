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
	
	///Returns this node's subnodes.
	public function children()
	{
		$children = array();
		foreach ($this as $key => $value) {
			if ($value instanceof Node) $children[] = $value;
		}
		return $children;
	}
	
	///Handles generic function calls.
	public function __call($name, array $args)
	{
		foreach ($this->children() as $child) {
			call_user_func_array(array($child, $name), $args);
		}
	}
}