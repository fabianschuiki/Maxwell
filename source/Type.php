<?php
/* Copyright © 2013 Fabian Schuiki */
use Objects\ConcreteType;
use Objects\TypeSet;

/**
 * Class containing helper functions for dealing with type objects.
 */
class Type
{
	static public function describe($object)
	{
		// Concrete types are shown either with their referenced definition's name if the reference has been resolved or the type is builtin, or the referenced definition ID.
		if ($object instanceof ConcreteType) {
			$ref = $object->getDefinition();
			$def = $ref->get(!preg_match('/^0\./', $ref->getId())); // causes references to builtin types to be resolved
			if ($def !== null) {
				return $def->getName();
			} else {
				return "@".$ref->getId();
			}
		}
		if ($object instanceof \Objects\FunctionArgumentType) {
			return static::describe($object->getType())." ".$object->getName();
		}
		if ($object instanceof \Objects\FunctionArgumentTupleType) {
			$a = array();
			foreach ($object->getArguments()->getElements() as $argument) {
				$a[] = static::describe($argument);
			}
			return "(".implode(", ", $a).")";
		}
		if ($object instanceof \Objects\FunctionType) {
			return static::describe($object->getInputs())." -> ".static::describe($object->getOutputs());
		}
		if ($object instanceof TypeSet) {
			$a = array();
			foreach ($object->getTypes()->getElements() as $t) {
				$a[] = static::describe($t);
			}
			return "{".implode(", ", $a)."}";
		}
		if ($object instanceof \Objects\InvalidType) {
			return "<invalid>";
		}
		if ($object instanceof \Objects\GenericType) {
			return "*";
		}

		// Seems like we're unable to handle the object.
		throw new \InvalidArgumentException("Unable to describe object ".vartype($object)." as type.");
	}

	/**
	 * Tries to reduce the FunctionArgumentTupleTypes in the $tuples array to
	 * a set of tuples with distinct lengths, where each tuple argument's type
	 * is the set of all argument types at this location.
	 */
	static public function unifyArgumentTuples(array $tuples)
	{
		$unified = array(); // unified tuples indexed by their lengths
		foreach ($tuples as $tuple) {
			$l = $tuple->getArguments()->getCount();
			if (!isset($unified[$l])) {
				$u = new \Objects\FunctionArgumentTupleType;
				$u->setArguments(new RepositoryObjectArray);
				$unified[$l] = $u;
			}
			$unifiedArguments = $u->getArguments();
			foreach ($tuple->getArguments()->getElements() as $index => $argument) {
				$ua = $unifiedArguments->get($index, false);
				if (!$ua) {
					$unifiedArguments->set($index, $argument);
				} else if ($ua->getType() instanceof TypeSet) {
					$ua->getType()->getTypes()->add($argument->getType());
				} else {
					$a = new RepositoryObjectArray;
					$a->add($ua->getType());
					$a->add($argument->getType());
					$s = new TypeSet;
					$s->setTypes($a);
					$ua->setType($s);
				}
			}
		}

		// Simplify the argument types.
		foreach ($unified as $u) {
			foreach ($u->getArguments()->getElements() as $arg) {
				$t = $arg->getType();
				if ($t instanceof TypeSet) {
					$arg->setType(static::simplifySet($t));
				}
			}
		}

		// Transform the array of unified tuples into a set of types.
		$a = new RepositoryObjectArray;
		foreach ($unified as $u) {
			$a->add($u);
		}
		$s = new TypeSet;
		$s->setTypes($a);
		return $s;
	}

	/**
	 * Simplifies the given set of types by removing duplicates and merging
	 * child type sets into the parent one.
	 */
	static public function simplifySet(\Objects\TypeSet $set)
	{
		$a = new RepositoryObjectArray;
		$flat = array();
		foreach ($set->getTypes()->getElements() as $child)
		{
			// Merge child sets.
			if ($child instanceof TypeSet) {
				$s = static::simplifySet($child);
				if ($s instanceof TypeSet) {
					foreach ($s->getTypes()->getElements() as $e) {
						$flat[] = $e;
					}
				} else {
					$flat[] = $s;
				}
				continue;
			}
			$flat[] = $child;
		}

		// Ignore duplicates.
		foreach ($flat as $child) {
			$duplicate = false;
			foreach ($a->getElements() as $e) {
				if (\Type::equal($child, $e)) {
					$duplicate = true;
					break;
				}
			}
			if (!$duplicate)
				$a->add($child);
		}

		if ($a->getCount() > 1) {
			$s = new TypeSet;
			$s->setTypes($a);
			return $s;
		} else {
			return $a->get(0);
		}
	}

	/**
	 * Returns true if the two types are equivalent, false otherwise.
	 */
	static public function equal($a,$b)
	{
		if ($a instanceof ConcreteType and $b instanceof ConcreteType) {
			return $a->getDefinition()->getId() === $b->getDefinition()->getId();
		}
		return false;
	}
}