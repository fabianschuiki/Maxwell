<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

class BinaryBuiltinOperator extends BuiltinRootObject implements \AbstractFunction
{
	protected $name;

	public function __construct(\Repository $repo, $id, $name, $typeA, $typeB, $typeR)
	{
		parent::__construct($repo, $id);
		$this->name = $name;
	}

	public function getName()
	{
		return $this->name;
	}

	public function getInputs($enforce = true)
	{
		throw new \RuntimeException("getInputs() should not be called on a builtin function.");
	}

	public function getOutputs($enforce = true)
	{
		throw new \RuntimeException("getInputs() should not be called on a builtin function.");
	}
}