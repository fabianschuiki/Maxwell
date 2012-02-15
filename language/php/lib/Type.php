<?php

class Type
{
	public $types = array('*');
	
	public function __construct()
	{
		$args = func_get_args();
		if (count($args)) {
			$this->types = (is_array($args[0]) ? $args[0] : $args);
		}
	}
	
	public function intersection(Type &$t)
	{
		if (in_array('*', $this->types)) return clone $t;
		if (in_array('*', $t->types)) return clone $this;
		return new Type(array_intersect($this->types, $t->types));
	}
	
	public function __toString()
	{
		return '{'.implode(', ', $this->types).'}';
	}
}
