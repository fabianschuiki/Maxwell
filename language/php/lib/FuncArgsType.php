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
}

class FuncArgsTypeField
{
	public $name;
	public $type;
	
	public function __toString()
	{
		return ($this->name ? $this->name.': ' : '').$this->type;
	}
}