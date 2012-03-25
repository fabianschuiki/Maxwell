<?php
namespace AST;

class ConstExpr extends Expr
{
	public $type;
	public $value;
	
	public function __construct($type, \Token $value)
	{
		assert($value->is($type));
		$this->type  = $type;
		$this->value = $value;
	}
}