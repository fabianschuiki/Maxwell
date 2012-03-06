<?php

class FuncArgsType extends Type
{
	public $fields = array();
	
	public function __toString()
	{
		return '('.implode(', ', $this->fields).')';
	}
	
	public function addField(TypeSet $type, $name = null)
	{
		$f = new FuncArgsTypeField;
		$f->name = $name;
		$f->type = $type;
		$this->fields[] = $f;
	}
	
	public function intersection(FuncArgsType $type)
	{
		$t = clone $this;
		if (!$t->intersect($type)) {
			return null;
		}
		return $t;
	}
	
	public function intersect(FuncArgsType $type)
	{
		$i = 0;
		for ($n = 0; $n < count($this->fields); $n++) {
			$field = $this->fields[$n];
			if ($field->name) {
				foreach ($type->fields as $tf) {
					if ($tf->name == $field->name) {
						$f = clone $field;
						$f->type = $field->type->intersection($tf->type);
						if (!$f) {
							return false;
						}
						$this->fields[$n] = $f;
					}
				}
			} else {
				if ($i >= count($type->fields)) {
					return false;
				}
				$f = clone $field;
				$f->type = $field->type->intersection($type->fields[$i++]->type);
				if (!$f->type) {
					return false;
				}
				$this->fields[$n] = $f;
			}
		}
		return true;
	}
	
	public function matches(Type $type)
	{
		if (!$type instanceof FuncArgsType) {
			return false;
		}
		$i = 0;
		foreach ($this->fields as $field) {
			if ($field->name) {
				foreach ($type->fields as $tf) {
					if ($tf->name == $field->name && !$field->type->matches($tf->type)) {
						return false;
					}
				}
			} else {
				if ($i >= count($type->fields) || !$field->type->matches($type->fields[$i++]->type)) {
					return false;
				}
			}
		}
		return true;
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

class FuncArgsTypeField
{
	public $name;
	public $type;
	
	public function __toString()
	{
		return ($this->name ? $this->name.':' : '').$this->type;
	}
}