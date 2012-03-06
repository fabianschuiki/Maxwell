<?php

class NamedType extends Type
{
	public $name;
	public $cast = null;
	
	public function __toString()
	{
		$s = $this->name;
		$c = $this->cost();
		if ($c > 0) {
			$s .= "°$c";
		}
		return $s;
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