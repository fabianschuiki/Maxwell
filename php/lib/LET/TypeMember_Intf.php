<?php
namespace LET;

class TypeMember_Intf extends TypeMember
{
	public $name;
	
	public function __construct(Scope $scope, TypeMember $member)
	{
		parent::__construct();
		
		$this->name  = strval($member->name());
		$this->type  = $member->type()->reduceToAbsolute($scope);
		$this->id    = $member->id;
		$this->scope = $scope;
	}
	
	public function name() { return $this->name; }
	
	public function reduceToInterface() { throw new \RuntimeExcpetion("TypeMember_Intf should never be asked for interface reduction"); }
}