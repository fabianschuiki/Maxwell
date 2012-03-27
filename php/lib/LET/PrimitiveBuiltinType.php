<?php
namespace LET;

class PrimitiveBuiltinType extends BuiltinType
{
	public $name;
	
	public function __construct(Scope $scope, $name)
	{
		assert(is_string($name));
		
		$this->name  = $name;
		$this->scope = $scope;
		
		$scope->add($this);
	}
	
	public function name()    { return $this->name; }
	public function members() { return array(); }
}