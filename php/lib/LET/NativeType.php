<?php
namespace LET;

abstract class NativeType extends Type
{
	abstract function name();
	public function details() { return "'{$this->name()}'"; }
	
	public function isSpecific() { return true; }
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new NativeType_Impl($scope, $this->name());
	}
}