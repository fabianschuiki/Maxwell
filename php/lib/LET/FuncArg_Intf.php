<?php
namespace LET;

class FuncArg_Intf extends FuncArg
{
	public $name;
	
	public function __construct(Scope $scope, FuncArg $arg)
	{
		parent::__construct();
		
		$type = $arg->type();
		$type = ($type instanceof ConcreteType ? $type->reduceToTypeExpr($scope) : $type->reduceToInterface($scope));
		
		$this->name  = strval($arg->name());
		$this->type  = $type;
		$this->scope = $scope;
	}
	
	public function name() { return $this->name; }
	
 	public function reduceToInterface() { throw new \RuntimeExcpetion("FuncArg_Intf should never be asked for reduction"); }
}