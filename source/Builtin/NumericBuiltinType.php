<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

class NumericBuiltinType extends BuiltinRootObject implements \NamedObject
{
	protected $name;

	public function setName($name)
	{
		$this->name = $name;
	}

	public function getName()
	{
		return $this->name;
	}
}