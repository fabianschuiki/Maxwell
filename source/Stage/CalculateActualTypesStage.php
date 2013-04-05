<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;
use Objects\InvalidType;
use Objects\GenericType;
use Objects\TypeSet;

class CalculateActualTypesStage extends DriverStage
{
	static public $verbosity = 1;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		if ($object instanceof \Objects\TypeInterface) {
			$possible = $object->getPossibleType();
			$required = $object->getRequiredType();
			$this->println(3, "Intersecting ".\Type::describe($possible)." and ".\Type::describe($required), $object->getId());

			// Add the required dependency.
			$this->addDependency($possible);
			$this->addDependency($required);

			// Catch the easy cases.
			if ($possible instanceof InvalidType or $required instanceof GenericType) {
				$object->setActualType(clone $possible);
			} else if ($required instanceof InvalidType) {
				throw new \RuntimeException("Required type of {$object->getId()} should not be the invalid type.");
			}

			// Otherwise try to find a match.
			else {
				$m = \Type::intersectSetOrConcreteType($possible, $required);
				$object->setActualType($m);
				if ($m instanceof InvalidType) {
					$this->println(2, "Try to find a cast from ".\Type::describe($possible)." to ".\Type::describe($required));
				}
			}

			// Show the output of the stage.
			$this->println(1, \Type::describe($object->getActualType()), $object->getId());
		}
	}
}