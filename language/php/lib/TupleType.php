<?php

class TupleType extends Type
{
	public $fields = array();
	
	public function __toString()
	{
		return '('.implode(', ', $this->fields).')';
	}
	
	public function addField(TypeSet $type, $name = null)
	{
		$f = new TupleTypeField;
		$f->name = $name;
		$f->type = $type;
		$this->fields[] = $f;
	}
	
	public function matches(Type $type)
	{
		if (!$type instanceof TubleType) {
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

class TupleTypeField
{
	public $name;
	public $type;
	
	public function __toString()
	{
		return ($this->name ? $this->name.': ' : '').$this->type;
	}
}