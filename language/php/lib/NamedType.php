<?php

class NamedType extends Type
{
	public $name;
	public $cast = null;
	
	public function __toString()
	{
		return $this->name.'['.$this->cost().']';
	}
	
	public function matches(Type $type)
	{
		return ($this->name == $type->name);
	}
	
	public function cost()
	{
		return ($this->cast ? count($this->cast) : 0);
	}
}