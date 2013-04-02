<?php
/* Copyright © 2013 Fabian Schuiki */

class BuiltinObjects
{
	protected $objects = array();
	protected $names = array();

	/**
	 * Creates the repository and populates it with all builtin objects.
	 */
	public function __construct(Repository $repo)
	{
		// int and real
		$type_int = new Builtin\NumericBuiltinType($repo, $this->makeId());
		$type_int->setName("int");
		$this->add($type_int);
		$type_real = new Builtin\NumericBuiltinType($repo, $this->makeId());
		$type_real->setName("real");
		$this->add($type_real);

		// Operators on int and real
		$mul_int_int = new Builtin\BinaryBuiltinOperator($repo, $this->makeId());
		$mul_int_int->setName("*");
		$this->add($mul_int_int);
	}

	private function add(\NameInterface $object)
	{
		$this->objects[$object->getId()] = $object;
		$this->names[$object->getId()] = $object->getName();
	}

	private $currentId = 1;
	private function makeId()
	{
		return "0.".($this->currentId++);
	}

	public function getObject($id)
	{
		if (!isset($this->objects[$id])) {
			throw new \InvalidArgumentException("No builtin object with ID $id known.");
		}
		return $this->objects[$id];
	}

	public function getObjectNames()
	{
		return $this->names;
	}
}