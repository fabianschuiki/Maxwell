<?php
namespace Interpreter;

abstract class Value
{
	abstract function type();
	abstract function value();
	
	public function set(Value $v)
	{
		global $issues;
		$issues[] = new \Issue(
			'error',
			"Unable to change value $this to $v."
		);
	}
	
	public function __toString() { return "{$this->typeDetails()} {$this->valueDetails()}"; }
	
	public function typeDetails()  { return $this->type()->details(); }
	public function valueDetails() { return $this->value(); }
}