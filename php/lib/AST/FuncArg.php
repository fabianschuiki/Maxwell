<?php
namespace AST;

class FuncArg extends Node
{
	public $type;
	public $name;
	
	public function __construct(Expr $type, \Token $name)
	{
		assert($name->is('identifier'));
		$this->type = $type;
		$this->name = $name;
	}
}