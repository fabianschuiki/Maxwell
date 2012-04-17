<?php
namespace LET;

class TypeMember_Intf extends TypeMember
{
	public $name;
	
	public function __construct(Scope $scope, TypeMember $member)
	{
		$type = $member->type();
		$type = ($type instanceof ConcreteType ? $type->reduceToTypeExpr($scope) : $type->reduceToInterface($scope));
		
		$this->name  = strval($member->name());
		$this->type  = $type;
		$this->scope = $scope;
	}
	
	public function name() { return $this->name; }
	
	public function reduceToInterface() { throw new \RuntimeExcpetion("TypeMember_Intf should never be asked for reduction"); }
}