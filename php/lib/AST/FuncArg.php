<?php
namespace AST;

class FuncArg extends Node
{
	public $type;
	public $name;
	
	public function __construct($type, \Token $name)
	{
		assert(!$type || $type instanceof Expr);
		assert($name->is('identifier'));
		
		$this->type = $type;
		$this->name = $name;
	}
}