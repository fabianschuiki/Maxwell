<?php
namespace Interpreter;

class Variable extends Value
{
	public $len;
	public $value;
	
	public function __construct(\LET\TypedNode $len, $value = null)
	{
		assert(!$value || $value instanceof Value);
		
		if (!$value) $value = new NilValue();
		
		$this->len   = $len;
		$this->value = $value; 
	}
	
	public function type()  { return $this->value->type(); }
	public function value() { return $this->value->value(); }
	
	public function set(Value $v)
	{
		$this->value = $v;
	}
}