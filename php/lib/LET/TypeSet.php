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
		foreach ($this->types as &$type) {
			$type = $type->reduce();
		}
		return $this;
	}
}