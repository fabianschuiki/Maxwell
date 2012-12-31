<?php
namespace C;

class GlobalVar extends Node
{
	public $signature;
	public $value;
	
	public function getDefinition()
	{
		return "{$this->signature} = {$this->value};";
	}
	
	public function getDeclaration()
	{
		return "extern {$this->signature};";
	}
	
	public function getStmt()
	{
		return $this->getDefinition();
	}
}