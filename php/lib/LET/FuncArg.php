<?php
namespace LET;

abstract class FuncArg extends Node
{
	abstract function type();
	abstract function name();
	
	public function details()
	{
		$type = $this->type();
		$type = ($type ? $type->details() : '?');
		
		return "$type {$this->name()}";
	}
}