<?php

class NamedType extends Type
{
	public $name;
	public $cast = null;
	
	public function __toString()
	{
		$s = $this->name;
		if ($this->cast) {
			$s .= '['.count($this->cast).']';
		}
		return $s;
	}
	
	public function cost()
	{
		if ($this->cast)
			return count($this->cast);
		return 0;
	}
	
	public function matches(Type $type)
	{
		return ($this->name == $type->name);
	}
}