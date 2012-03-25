<?php
namespace LET;

class Node
{
	///Returns the type of this LET node, which is its class name without the LET namespace.
	public function type()
	{
		return preg_replace('/^'.preg_quote(__NAMESPACE__.'\\').'/', '', get_class($this));
	}
	
	///Returns a description of this LET node.
	public function desc()
	{
		$str = substr(get_class($this), 4);
		if (method_exists($this, 'details')) {
			$str .= " {$this->details()}";
		}
		return $str;
	}
}