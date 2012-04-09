<?php
namespace Interpreter;

class ConcreteValue extends Value
{
	public $type;
	public $value;
	
	public function __construct(\LET\Type $type, $value)
	{
		$this->type  = $type;
		$this->value = $value;
	}
	
	public function type()  { return $this->type; }
	public function value() { return $this->value; }
}