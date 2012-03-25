<?php
namespace LET;

abstract class FuncArg extends Node
{
	abstract function type();
	abstract function name();
	
	public function details()
	{
		return "{$this->type()} {$this->name()}";
	}
}