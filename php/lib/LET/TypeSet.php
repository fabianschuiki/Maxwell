<?php
namespace LET;

class TypeSet extends Type
{
	public $types;
	
	public function __construct(Scope $scope, array $types)
	{
		$this->types = $types;
		$this->scope = $scope;
	}
	
	public function details()
	{
		$types = array_map(function($type){ return $type->details(); }, $this->types);
		$types = implode(', ', $types);
		
		return '{'.$types.'}';
	}
	
	public function children() { return $this->types; }
	
	public function reduce()
	{
		$this->types = array_map(function($t) { return $t->reduce(); }, $this->types);
		if (count($this->types) == 1) return $this->types[0];
		return $this;
	}
}