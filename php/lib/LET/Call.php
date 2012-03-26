<?php
namespace LET;

abstract class Call extends Expr
{
	abstract function callee();
	abstract function args();
	
	public function details()
	{
		return "{$this->callee()->details()} (".implode(", ", array_map(function($arg){ return ($arg ? $arg->details() : '?'); }, $this->args())).")";
	}
}