<?php

class TupleType
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