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
		//echo "       type before:       {$this->type()->details()}\n";
		if ($type instanceof TypeTuple) {
			$pairs = TypeTuple::fieldPairs($this->unconstrainedType(), $type);
			foreach ($pairs as $a => $b) {
				$this->fields[$a]->imposeTypeConstraint($type->fields[$b]);
			}
		}
		//echo "       type after:        {$this->type()->details()}\n";
		//echo "       lastConfirmedType: {$this->lastConfirmedType->details()}\n";
		parent::imposeTypeConstraint($type);
	}
	
	public function notifyNodeChangedType(Node $node)
	{
		if (in_array($node, $this->fields(), true)) {
			echo "\033[32mnotify\033[0m: {$this->desc()} field {$node->details()} changed\n";
			//$this->propagateTypeChange($this);
			$this->maybeTypeChanged();
		}
		parent::notifyNodeChangedType($node);
	}
}