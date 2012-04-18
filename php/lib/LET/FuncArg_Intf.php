<?php
namespace LET;

class FuncArg_Intf extends FuncArg
{
	public $name;
	
	public function __construct(Scope $scope, FuncArg $arg)
	{
		parent::__construct();
		
		$this->name  = strval($arg->name());
		$this->type  = $arg->type()->reduceToAbsolute($scope);
		$this->scope = $scope;
	}
	
	public function name() { return $this->name; }
	
 	public function reduceToInterface() { throw new \RuntimeExcpetion("FuncArg_Intf should never be asked for interface reduction"); }
}