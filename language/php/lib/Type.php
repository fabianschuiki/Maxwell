<?php

abstract class Type
{
	abstract public function match(Type $type, &$vars = array(), $initial = true);
	public function resolveVars() {}
	//abstract public function cost();
}