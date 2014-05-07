<?php
/* Copyright © 2013 Fabian Schuiki */

/**
 * Container class for all the builtin types of the language.
 */
class BuiltinObjects
{
	protected $objects = array();
	protected $names = array();

	/**
	 * Creates the repository and populates it with all builtin objects.
	 */
	public function __construct(Repository $repo)
	{
		// Root type for all types.
		$type = new Builtin\NumericBuiltinType($repo, $this->makeId(), "_type");
		$this->add($type);
		$type_weird = new Builtin\NumericBuiltinType($repo, $this->makeId(), "weird");
		$this->add($type_weird);

		// int and real
		$type_int = new Builtin\NumericBuiltinType($repo, $this->makeId(), "int", $type);
		$this->add($type_int);
		$type_real = new Builtin\NumericBuiltinType($repo, $this->makeId(), "real", $type);
		$this->add($type_real);

		// Casts.
		$cast_ir = new Builtin\BuiltinCast($repo, $this->makeId(), $type_int, $type_real);
		$this->add($cast_ir);
		$cast_ri = new Builtin\BuiltinCast($repo, $this->makeId(), $type_real, $type_int);
		$this->add($cast_ri);

		// Operators on int and real
		foreach (array("*", "+", "-") as $op) {
			$mul_ii = new Builtin\BinaryBuiltinOperator($repo, $this->makeId(), $op, $type_int, $type_int, $type_int);
			$this->add($mul_ii);
			$mul_ir = new Builtin\BinaryBuiltinOperator($repo, $this->makeId(), $op, $type_int, $type_real, $type_real);
			$this->add($mul_ir);
			$mul_ri = new Builtin\BinaryBuiltinOperator($repo, $this->makeId(), $op, $type_real, $type_int, $type_real);
			$this->add($mul_ri);
			$mul_rr = new Builtin\BinaryBuiltinOperator($repo, $this->makeId(), $op, $type_real, $type_real, $type_real);
			$this->add($mul_rr);
		}
	}

	private function add(NamedObject $object)
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