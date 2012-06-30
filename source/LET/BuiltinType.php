<?php
namespace LET;

abstract class BuiltinType extends ConcreteType
{
	public function details() {	return $this->name(); }
}