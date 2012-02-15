<?php

class Scope
{
	public $parent;
	public $names = array();
	
	public function __construct($parent = null)
	{
		$this->parent = $parent;
	}
	
	public function find($name)
	{
		if (isset($this->names[$name]))
			return $this->names[$name];
		if ($this->parent)
			return $this->parent->find($name);
		return null;
	}
}
