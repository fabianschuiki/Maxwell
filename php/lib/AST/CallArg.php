<?php
namespace AST;

class CallArg extends Node
{
	public $name;
	public $expr;
	
	public function __construct($name, Expr $expr)
	{
		assert(!$name || ($name instanceof Token && $name->is('identifier')));
		$this->name = $name;
		$this->expr = $expr;
	}
	
	public function nice() { "Call argument"; }
}