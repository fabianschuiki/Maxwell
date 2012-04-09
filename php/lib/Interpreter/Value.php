<?php
namespace Interpreter;

class Value
{
	public $type;
	public $value;
	
	public function __construct(\LET\Type $type, $value)
	{
		$this->type  = $type;
		$this->value = $value;
	}
}