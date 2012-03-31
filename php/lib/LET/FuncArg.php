<?php
namespace LET;

abstract class FuncArg extends TypedNode
{
	public $type;
	
	abstract function name();
	
	public function details()
	{
		$type = $this->type();
		$type = ($type ? $type->details() : '?');
		
		return "$type {$this->name()}";
	}
	public function unconstrainedType() { return $this->type; }
	
	public function reduce()
	{
		if ($this->type()) $this->type = $this->type()->reduce();
		return $this;
	}
}