<?php
namespace LET;

class ConcreteType_Intf extends ConcreteType
{
	public $name;
	public $members;
	
	public function __construct(Scope $scope, ConcreteType $type)
	{
		$subscope = $type->subscope->reduceToInterface($scope);
		
		$members = array();
		foreach ($type->members() as $member) {
			$members[] = $member->reduceToInterface($subscope);
		}
		
		$this->name     = strval($type->name());
		$this->members  = $members;
		$this->subscope = $subscope;
		$this->scope    = $scope;
	}
	
	public function name()    { return $this->name; }
	public function members() { return $this->members; }
	
	public function reduceToInterface() { throw new \RuntimeExcpetion("ConcreteType_Intf should never be asked for reduction"); }
}