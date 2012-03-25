<?php
namespace LET;

class Node
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
}