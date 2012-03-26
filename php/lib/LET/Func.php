<?php
namespace LET;

abstract class Func extends Node
{	
	abstract function name();
	abstract function inputs();
	abstract function outputs();
	abstract function stmts();
	abstract function subscope();
	
	public function details()
	{
		$det = function($arg){ return $arg->details(); };
		return "'{$this->name()}' (".implode(", ", array_map($det, $this->inputs())).") -> (".implode(", ", array_map($det, $this->outputs())).")";
	}
	
	public function children()
	{
		$children = array_merge($this->inputs(), $this->outputs(), array($this->subscope()), $this->stmts());
		return $children;
	}
}