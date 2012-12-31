<?php

class IDProvider
{
	protected $id = 0;
	static protected $stack = array();
	
	public function push()
	{
		array_push(static::$stack, $this);
	}
	
	public function pop()
	{
		$popped = array_pop(static::$stack);
		assert($popped === $this);
	}
	
	static public function makeID()
	{
		if (count(static::$stack) == 0) trigger_error("Trying to make ID with no IDProvider in place.", E_USER_ERROR);
		return static::$stack[count(static::$stack) - 1]->id++;
	}
}