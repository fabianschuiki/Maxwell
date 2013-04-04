<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;
use Objects\InvalidType;
use Objects\GenericType;
use Objects\TypeSet;

class CalculateActualTypesStage extends DriverStage
{
	static public $verbosity = 2;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		if ($object instanceof \Objects\TypeInterface) {
			$possible = $object->getPossibleType();
			$required = $object->getRequiredType();
			$this->println(2, "intersecting ".\Type::describe($possible)." and ".\Type::describe($required), $object->getId());

			// Catch the easy cases.
			if ($possible instanceof InvalidType or $required instanceof GenericType) {
				$object->setActualType($possible);
			} else if ($required instanceof InvalidType) {
				throw new \RuntimeException("Required type of {$object->getId()} should not be the invalid type.");
			}

			// Otherwise try to find a match.
			else {
				$object->setActualType(\Type::intersectSetOrConcreteType($possible, $required));
			}

			// Show the output of the stage.
			$this->println(1, \Type::describe($object->getActualType()), $object->getId());
		}
	}
}