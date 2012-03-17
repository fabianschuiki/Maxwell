<?php

class TypeVar extends Type
{
	public $name;
	public $type;
	private $id;
	static private $currentID = 0;
	
	public function __construct($name)
	{
		$this->name = $name;
		$this->id = static::$currentID++;
	}
	
	public function __toString()
	{
		$t = $this->name.$this->id;
		if ($this->type) {
			$t .= "[{$this->type}]";
		} else {
			$t .= '?';
		}
		return $t;
	}
	
	public function match(Type $type, &$vars = array(), $initial = true)
	{
		if (isset($vars[$this->id])) {
			$this->type = $vars[$this->id];
		} else {
			$this->type = null;
		}
		$str = strval($this);
		
		if ($this->type) {
			$this->type = $this->type->match($type, $vars, false);
		} else {
			$this->type = $type;
		}
		
		//echo "matching var $str against $type -> $this\n";
		$vars[$this->id] = $this->type;
		if ($this->type instanceof TypeSet) {
			return $this;
		} else {
			return $this->type;
		}
	}
	
	public function isGeneric()
	{
		return true;
	}
}