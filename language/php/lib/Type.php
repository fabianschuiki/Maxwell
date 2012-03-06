<?php

abstract class Type
{
	abstract public function matches(Type $type);
	abstract public function cost();
}