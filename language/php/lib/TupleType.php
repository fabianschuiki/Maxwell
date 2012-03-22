<?php

class TupleType extends Type
{
	public $fields = array();
	public $strict = true;
	
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
		$i  = 0;
		$fi = 0;
		$bfused = array();
		foreach ($this->fields as $af) {
			if ($af->name) {
				$bf = $type->getField($af->name);
				if (!$bf) {
					$bf = $type->getField($fi);
				}
			} else {
				$bf = $type->getField($i++);
			}
			if (!$bf) {
				//if ($this->strict) {
					return null;
				/*} else {
					$match->addField($af->type, $af->name);
				}*/
			} else {
				$bfused[] = $bf->name;
				$m = $af->type->match($bf->type, $vars, false);
				if (!$m) {
					return null;
				}
				$match->addField($m, ($af->name ? $af->name : $bf->name));
				$fi++;
			}
		}
		foreach ($type->fields as $bf) {
			if (in_array($bf->name, $bfused)) {
				continue;
			}
			$match->addField($bf->type, $bf->name);
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
	
	public function isGeneric()
	{
		foreach ($this->fields as $f) {
			if ($f->type->isGeneric()) {
				return true;
			}
		}
		return false;
	}
	
	public function getAbstractionLevel()
	{
		$l = 0;
		foreach ($this->fields as $f) {
			if ($f->type) {
				$l += $f->type->getAbstractionLevel();
			}
		}
		return $l;
	}
	
	public function cost()
	{
		$cost = 0;
		foreach ($this->fields as $f) {
			if ($f->type) {
				$cost += $f->type->cost();
			}
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