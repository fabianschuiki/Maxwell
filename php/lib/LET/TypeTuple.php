<?php
namespace LET;

class TypeTuple extends Type
{
	public $fields;
	
	public function __construct(Scope $scope, array $fields)
	{
		$this->fields = $fields;
		$this->scope  = $scope;
	}
	
	public function details()
	{
		$fields = array();
		foreach ($this->fields as $name => $field) {
			$str = $field->details();
			if (is_string($name)) $str = "$name: $str";
			$fields[] = $str;
		}
		$fields = implode(', ', $fields);
		
		return "($fields)";
	}
	
	public function children() { return array_values($this->fields); }
	
	public function isConcrete()
	{
		foreach ($this->fields as $name => $field) {
			if (!$field->isConcrete()) return false;
		}
		return true;
	}
}