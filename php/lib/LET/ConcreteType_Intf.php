<?php
namespace LET;

class ConcreteType_Intf extends ConcreteType
{
	public $name;
	public $members;
	
	public function __construct(Scope $scope, ConcreteType $type)
	{
		$this->name = strval($type->name());
	}
	
	public function name()    { return $this->name; }
	public function members() { return $this->members; }
	
	public function reduceToInterface() { throw new \RuntimeExcpetion("ConcreteType_Intf should never be asked for reduction"); }
}