<?php
namespace LET;

class GenericType extends Type
{
	public function details() { return "*"; }
	public function reduceToTypeExpr(Scope $scope) { return new GenericType; }
}