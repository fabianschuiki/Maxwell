<?php
namespace LET;

abstract class Func extends Node
{	
	abstract function name();
	abstract function inputs();
	abstract function outputs();
	
	public function details()
	{
		$det = function($arg){ return $arg->details(); };
		return "'{$this->name()}' (".implode(", ", array_map($det, $this->inputs())).") -> (".implode(", ", array_map($det, $this->outputs())).")";
	} 
}