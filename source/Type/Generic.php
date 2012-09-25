<?php
namespace Type;

/** Generic type that is compatible with all other types. */
class Generic extends Type
{
	static public function make()
	{
		$t = new self;
		$t->generateId();
		return $t;
	}
}