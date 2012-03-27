<?php
namespace LET;

abstract class Type extends Node
{
	abstract function name();
	abstract function members();
	
	public function details()
	{
		return "'{$this->name()}' {".implode(", ", array_map(function($m){ return $m->details(); }, $this->members))."}";
	}
	
	public function children()
	{
		return $this->members();
	}
	
	public function type()
	{
		return new InferredType\Named($this->name());
	}
}