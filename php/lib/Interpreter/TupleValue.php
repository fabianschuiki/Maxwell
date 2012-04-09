<?php
namespace Interpreter;

class TupleValue extends Value
{
	public $fields;
	
	public function __construct()
	{
		$this->fields = array();
	}
	
	public function type()  { return null; }
	public function value() { return null; }
	
	public function typeDetails()
	{
		$types = array();
		foreach ($this->fields as $name => $value) $types[] = "$name: {$value->typeDetails()}";
		return "(".implode(', ', $types).")";
	}
	public function valueDetails()
	{
		$values = array();
		foreach ($this->fields as $name => $value) $values[] = "$name: {$value->valueDetails()}";
		return "(".implode(', ', $values).")";
	}
}