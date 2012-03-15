<?php

class TupleType extends Type
{
	public $fields = array();
// 	
	
	public function __toString()
	{
		return '('.implode(', ', $this->fields).')';
	}
	
	public function addField(Type $type, $name = null)
	{
		$f = new TupleTypeField;
		$f->name = $name;
		$f->type = $type;
		$this->fields[] = $f;
	}
	
	public function getField($ni)
	{
		if (is_string($ni)) {
			foreach ($this->fields as $f) {
				if ($f->name == $ni) {
					return $f;
				}
			}
		} else {
			if ($ni >= 0 && $ni < count($this->fields)) {
				return $this->fields[$ni];
			}
		}
		return null;
	}
	
	public function match(Type $type, &$vars = array(), $initial = true)
	{
		if ($type instanceof TypeSet || $type instanceof TypeVar) {
			return $type->match($this, $vars, $initial);
		}
		if (!$type instanceof TupleType) {
			return null;
		}
		
		$match = new TupleType;
		$i = 0;
		foreach ($this->fields as $af) {
			if ($af->name) {
				$bf = $type->getField($af->name);
			} else {
				$bf = $type->getField($i++);
			}
			if (!$bf) {
				return null;
			}
			
			$m = $af->type->match($bf->type, $vars, false);
			if (!$m) {
				return null;
			}
			$match->addField($m, $af->name);
		}
		
		//Resolve type variables.
		if ($initial) {
			$match->resolveVars();
		}
		
		return $match;
	}
	
	public function resolveVars()
	{
		foreach ($this->fields as $af) {
			if ($af->type instanceof TypeVar) {
				$af->type = $af->type->type;
			} else {
				$af->type->resolveVars();
			}
		}
	}
	
	public function cost()
	{
		$cost = 0;
		foreach ($this->fields as $f) {
			$cost += $f->type->cost();
		}
		return $cost;
	}
}

class TupleTypeField
{
	public $name;
	public $type;
	
	public function __toString()
	{
		return ($this->name ? $this->name.':' : '').$this->type;
	}
}