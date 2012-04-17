<?php
namespace LET;

class FuncArg_Intf extends FuncArg
{
	public $name;
	public $type;
	
	public function __construct(Scope $scope, FuncArg $arg)
	{
		$this->name  = strval($arg->name());
		$this->type  = $arg->type()->reduceToInterface($scope);
		$this->scope = $scope;
	}
	
	public function name() { return $name; }
	
 	public function reduceToInterface() { throw new \RuntimeExcpetion("FuncArg_Intf should never be asked for reduction"); }
}