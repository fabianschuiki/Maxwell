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
}