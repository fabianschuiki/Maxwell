<?php
namespace LET;

class FuncArg_Impl extends FuncArg
{
	public $type;
	public $name;
	
	public function __construct(Scope $scope, Type $type, $name)
	{
		assert(is_string($name));
		$this->type  = $type;
		$this->name  = $name;
		$this->scope = $scope;
		
		$scope->add($this);
	}
	
	public function unconstrainedType() { return $this->type; }
	public function name()              { return $this->name; }
}