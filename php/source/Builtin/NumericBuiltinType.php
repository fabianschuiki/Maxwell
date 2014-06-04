<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Builtin;

class NumericBuiltinType extends BuiltinRootObject implements \NamedObject, \TypedObject
{
	protected $name;
	protected $type;

	public function __construct(\Repository $repo, $id, $name, $type = null)
	{
		parent::__construct($repo, $id);
		$this->name = $name;
		$r = new \RepositoryObjectReference($repo);
		$r->set($type);
		$ct = new \Objects\ConcreteType;
		$ct->setDefinition($r);
		$this->type = $ct;
	}

	public function setName($name)
	{
		$this->name = $name;
	}

	public function getName()
	{
		return $this->name;
	}

	public function getPossibleType()
	{
		return $this->type;
	}
}