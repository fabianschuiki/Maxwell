<?php

class TypeSet
{
	public $types = array('any');
	
	public function __toString()
	{
		return implode(',', $this->types);
	}
}