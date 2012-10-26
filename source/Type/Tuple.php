<?php
namespace Type;

/** Tuple type that represents the types of a tuple's fields. */
class Tuple extends Type
{
	static public function makeWithFields(array $fields)
	{
		$t = new self;
		$t->setFields($fields);
		return $t;
	}
	
	protected $fields;
	
	public function setFields(array $f) { $this->fields = $f; }
	public function getFields() { return $this->fields; }
}