<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

abstract class BuiltinObject
{
	abstract public function getId();
	
	public function get($property, $enforce = true)
	{
		$getter = "get".ucfirst($property);
		return $this->$getter($enforce);
	}
}