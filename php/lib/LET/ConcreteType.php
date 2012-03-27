<?php
namespace LET;

abstract class ConcreteType extends Type
{
	abstract function name();
	abstract function members();
	
	public function isSpecific()
	{
		foreach ($this->members() as $member) {
			$type = $member->type();
			if (!$type || !$type->isSpecific()) return false;
		}
		return true;
	}
	
	public function details()
	{
		return "'{$this->name()}' {".implode(", ", array_map(function($m){ return $m->details(); }, $this->members))."}";
	}
	
	public function children()
	{
		return $this->members();
	}
}