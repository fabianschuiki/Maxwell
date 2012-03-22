<?php

abstract class Type
{
	abstract public function match(Type $type, &$vars = array(), $initial = true);
	public function resolveVars() {}
	public function isGeneric() { return false; }
	public function getAbstractionLevel() { return 0; }
	//abstract public function cost();
}