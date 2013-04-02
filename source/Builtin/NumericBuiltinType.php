<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

class NumericBuiltinType extends BuiltinObject implements \NameInterface
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