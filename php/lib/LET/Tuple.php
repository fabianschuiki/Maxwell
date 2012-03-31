<?php
namespace LET;

abstract class Tuple extends Expr
{
	abstract function fields();
	
	public function details()
	{
		$fields = array();
		foreach ($this->fields() as $name => $field) {
			$str = $field->details();
			if (is_string($name)) $str = "$name: $str";
			$fields[] = $str;
		}
		$fields = implode(', ', $fields);
		
		return "($fields)";
	}
	
	public function children() { return array_values($this->fields()); }
	
	public function unconstrainedType()
	{
		$fields = array();
		foreach ($this->fields() as $name => $field) {
			$type = $field->type();
			if (!$type) return null;
			$fields[$name] = $type;
		}
		return new TypeTuple($this->scope, $fields);
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		parent::imposeTypeConstraint($type);
		
		if ($type instanceof TypeTuple) {
			$pairs = TypeTuple::fieldPairs($this->unconstrainedType(), $type);
			foreach ($pairs as $a => $b) {
				$this->fields[$a]->imposeTypeConstraint($type->fields[$b]);
			}
		}
	}
}