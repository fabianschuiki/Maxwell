<?php
namespace LET;

class Func_Intf extends Func
{
	public $name;
	public $inputs;
	public $outputs;
	public $subscope;
	
	public function __construct(Scope $scope, Func $func)
	{
		$subscope = $func->subscope->reduceToInterface($scope);
		$subscope->node = $this;
		
		$inputs  = array();
		$outputs = array();
		foreach ($func->inputs()  as $i) $inputs[]  = $i->reduceToInterface($subscope);
		foreach ($func->outputs() as $o) $outputs[] = $o->reduceToInterface($subscope);
		
		$this->name     = strval($func->name());
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		$this->subscope = $subscope;
		$this->scope    = $scope;
	}
	
	public function name()     { return $this->name; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function subscope() { return $this->subscope; }
	public function stmts()    { return array(); }
	
	public function reduceToInterface() { throw new \RuntimeExcpetion("Func_Intf should never be asked for reduction"); }
}