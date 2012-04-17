<?php
namespace LET;

class GenericType extends Type
{
	public function details() { return "*"; }
	public function reduceToInterface(Scope $scope) { return new GenericType; }
}