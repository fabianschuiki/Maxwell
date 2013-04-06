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

		if ($object instanceof \Objects\CallInterface) {
			$this->process($object->getCallCandidates());
		}

		if ($object instanceof \Objects\TypeInterface) {
			$possible = $object->getPossibleType();
			$required = $object->getRequiredType();
			$this->println(2, "Intersecting ".\Type::describe($possible)." and ".\Type::describe($required), $object->getId());

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
				if ($m instanceof InvalidType) {
					$this->tryCast($object, $possible, $required);
				} else {
					$object->setActualType($m);
				}
			}

			// Show the output of the stage.
			$this->println(1, \Type::describe($object->getActualType()), $object->getId());
		}
	}

	private function tryCast(\RepositoryObject $object, $from, $to)
	{
		$this->println(1, "Try to find a cast from ".\Type::describe($from)." to ".\Type::describe($to), $object->getId());

		// Assemble a list of available cast functions.
		$castIds = array();
		$externals = $this->repository->getImportedNamesForObject($object->getId());
		foreach ($externals as $externalId => $externalName) {
			if ($externalName == "cast") {
				$castIds[] = $externalId;
			}
		}

		// Find the cast that matches the types.
		$casts = array();
		foreach ($castIds as $castId) {
			$f = $this->repository->getObject($castId);
			$ft = $f->getActualType(false);
			if (!$ft)
				$ft = $f->getPossibleType();
			$input = $ft->getInputs()->getArguments()->get(0)->getType();
			$output = $ft->getOutputs()->getArguments()->get(0)->getType();

			// The cast should have unique results.
			if ($input instanceof TypeSet || $output instanceof TypeSet) {
				throw new \RuntimeException("Expecting cast {$f->getId()} to have non-set input and output types, got ".\Type::describe($input)." to ".\Type::describe($output)." instead.");
			}

			// Find the intersection between the input and output types.
			$im = \Type::intersectSetOrConcreteType($from, $input);
			$om = \Type::intersectSetOrConcreteType($to, $output);
			$this->println(3, "Inspecting cast {$f->getId()} from ".\Type::describe($input)." to ".\Type::describe($output).". Match is from ".\Type::describe($im)." to ".\Type::describe($om), $object->getId());

			// If the match is valid, keep the cast around.
			if (!$im instanceof InvalidType && !$om instanceof InvalidType) {
				$casts[] = $f;
			}
		}

		// If there is a cast available, use it.
		if (count($casts) > 1) {
			throw new \RuntimeException("More than one cast is a viable conversion from ".\Type::describe($from)." to ".\Type::describe($to).".");
		} else if (count($casts) == 1) {
			$f = $casts[0];
			$ft = $f->getActualType(false);
			if (!$ft)
				$ft = $f->getPossibleType();

			// Actually create a cast type.
			$ct = new \Objects\CastType;
			$ct->setFromRef($from, $this->repository);
			$ct->setToRef($to, $this->repository);
			$ct->setCost(1); // needs to be variable in the future
			$ct->setFuncRef($f, $this->repository);

			// Log the cast use.
			$this->println(2, "Using cast {$f->getId()} ".\Type::describe($ct), $object->getId());

			/*$object->setActualTypeRef($ft->getOutputs()->getArguments()->get(0)->getType(), $this->repository);*/
			$object->setActualType($ct);
			return;
		}

		// In case we've found nothing, simply return the invalid type.
		$object->setActualType(new InvalidType);
	}
}