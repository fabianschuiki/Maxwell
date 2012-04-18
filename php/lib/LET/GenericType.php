<?php
namespace LET;

class GenericType extends Type
{
	public function details() { return "*"; }
	public function reduceToAbsolute(Scope $scope) { return new GenericType; }
}