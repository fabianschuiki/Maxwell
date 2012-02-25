<?php

class Scope
{
	static private $currentIndex = 0;
	public $parent;
	public $names = array();
	public $index;
	
	public function __construct($parent = null)
	{
		$this->parent = $parent;
		$this->index = static::$currentIndex++;
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
