<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

class BuiltinCast extends BuiltinRootObject implements \AbstractFunction
{
	protected $type;

	public function __construct(\Repository $repo, $id, $typeA, $typeR)
	{
		parent::__construct($repo, $id);

		$ar = new \RepositoryObjectReference($this->repository);
		$ar->set($typeA);
		$at = new \Objects\ConcreteType;
		$at->setDefinition($ar);
		$a = new \Objects\FunctionArgumentType;
		$a->setName("a");
		$a->setType($at);

		$rr = new \RepositoryObjectReference($this->repository);
		$rr->set($typeR);
		$rt = new \Objects\ConcreteType;
		$rt->setDefinition($rr);
		$r = new \Objects\FunctionArgumentType;
		$r->setName("r");
		$r->setType($rt);

		// Inputs
		$ina = new \RepositoryObjectArray($this->repository);
		$ina->add($a);
		$in = new \Objects\FunctionArgumentTupleType;
		$in->setArguments($ina);

		// Outputs
		$outa = new \RepositoryObjectArray($this->repository);
		$outa->add($r);
		$out = new \Objects\FunctionArgumentTupleType;
		$out->setArguments($outa);

		// Function
		$f = new \Objects\FunctionType;
		$f->setInputs($in);
		$f->setOutputs($out);
		$this->type = $f;
		$f->setParent($this, "actualType", null);
	}

	public function getName()
	{
		return "cast";
	}

	public function getInputs()
	{
		throw new \RuntimeException("getInputs() should not be called on a builtin function.");
	}

	public function getOutputs()
	{
		throw new \RuntimeException("getInputs() should not be called on a builtin function.");
	}

	public function getPossibleType()
	{
		return $this->type;
	}
	public function getActualType()
	{
		return $this->type;
	}
}