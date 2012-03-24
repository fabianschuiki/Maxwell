<?php

class NamedType extends Type
{
	public $name;
	public $cast = null;
	
	public function __construct($name = null)
	{
		$this->name = $name;
	}
	
	public function __toString()
	{
		$s = $this->name;
		$c = $this->cost();
		if ($c > 0) {
			$s .= "°$c";
		}
		return $s;
	}
	
	public function match(Type $type, &$vars = array(), $initial = true)
	{
		if ($type instanceof TypeSet || $type instanceof TypeVar) {
			return $type->match($this, $vars, $initial);
		}
		if (!$type instanceof NamedType) {
			return null;
		}
		
		/*if ($this->name[0] == '@') {
			if (!isset($vars[$this->name])) {
				echo "{$this->name} := $type\n";
				$vars[$this->name] = clone $type;
				return $vars[$this->name];
			} else {
				echo "matching {$this->name} against $type\n";
				return $vars[$this->name]->match($type, $vars);
			}
		} else if ($type->name[0] == '@') {
			return $type->match($this, $vars);
		}*/
		
		if ($this->name == $type->name) {
			return $this;
		}
		return null;
	}
	
	public function cost()
	{
		return ($this->cast ? count($this->cast) : 0);
	}
}