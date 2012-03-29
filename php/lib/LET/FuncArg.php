<?php
namespace LET;

abstract class FuncArg extends TypedNode
{
	//abstract function type();
	abstract function name();
	
	public function details()
	{
		$type = $this->type();
		$type = ($type ? $type->details() : '?');
		
		return "$type {$this->name()}";
	}
}