<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;
use Objects\InvalidType;
use Objects\GenericType;
use Objects\TypeSet;

class CalculateActualTypesStage extends DriverStage
{
	static public $verbosity = 0;

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
				$object->setActualTypeRef($possible, $this->repository);
			} else if ($required instanceof InvalidType) {
				throw new \RuntimeException("Required type of {$object->getId()} should not be the invalid type.");
			}

			// Otherwise try to find a match.
			else {
				$m = \Type::intersectSetOrConcreteType($possible, $required);

				// Check for special conversions for named types.
				if ($possible instanceof \Objects\NamedType && $required instanceof \Objects\NamedType)
				{
					// Check whether a mapping from a struct to its inherited struct is requested.
					if ($m instanceof InvalidType) {
						$m = $this->tryInheritanceMapping($object, $possible, $required);
					}
					// Check whether an interface mapping is requested.
					if ($m instanceof InvalidType) {
						$m = $this->tryInterfaceMapping($object, $possible, $required);
					}
				}

				// Otherwise simply try to go with a regular cast.
				if ($m instanceof InvalidType) {
					$m = $this->tryCast($object, $possible, $required);
				}

				$object->setActualType($m);
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

		// Throw an exception. Maybe this prevents the programmer from doing bad things?
		throw new \RuntimeException("No cast found from ".\Type::describe($from)." to ".\Type::describe($to).".");
	}

	private function tryInheritanceMapping(\RepositoryObject $object, $from, $to)
	{
		// Extract the two type definitions and make sure to only operate on proper type definitions.
		$defFrom = $from->getDefinition();
		$defTo = $to->getDefinition();
		if (!$defFrom instanceof \Objects\TypeDefinition || !$defTo instanceof \Objects\TypeDefinition) {
			return new InvalidType;
		}
		$desc = "from {$defFrom->getID()} to {$defTo->getId()}";
		$this->println(2, "Maybe performing inheritance translation $desc", $object->getId());

		// For both look for a structure type.
		$structFrom = null;
		$structTo = null;
		foreach ($defFrom->getTypes()->getElements() as $type) {
			if ($type instanceof \Objects\StructureType) {
				if ($structFrom !== null) {
					throw new \RuntimeException("Type {$defFrom->getId()} has multiple structural type specifiers.");
				}
				$structFrom = $type;
			}
		}
		foreach ($defTo->getTypes()->getElements() as $type) {
			if ($type instanceof \Objects\StructureType) {
				if ($structTo !== null) {
					throw new \RuntimeException("Type {$defTo->getId()} has multiple structural type specifiers.");
				}
				$structTo = $type;
			}
		}

		// If there are no structure type specifiers available an inheritance mapping is not possible.
		if ($structFrom === null || $structTo === null) {
			$this->println(2, "Inheritance mapping not possible $desc", $object->getId());
			return new InvalidType;
		}

		// Find an inheritance in $to that matches $from.
		foreach ($structFrom->getInherits()->getElements() as $i) {
			$t = $i->getType();
			if (!$t instanceof \Objects\NamedType) {
				throw new \RuntimeException("Inherited type {$t->getId()} expected to be a named type, got ".\Type::describe($t)." instead.");
			}
			$def = $t->getDefinition();
			$this->println(3, "Trying to map {$defTo->getId()} from {$def->getId()}", $object->getId());
			if ($def->getId() == $defTo->getId()) {
				/*$ref = new \RepositoryObjectReference($this->repository);
				$ref->set($def);
				$nt = new \Objects\NamedType;
				$nt->setName($def->getName());
				$nt->setDefinition($ref);
				return $nt;*/
				$imt = new \Objects\InheritanceMappedType;
				$imt->setTypeRef($from, $this->repository);
				$imt->setStructRef($structFrom, $this->repository);
				$imt->setInheritanceRef($i, $this->repository);
				return $imt;
			}
		}
		return new InvalidType;
	}

	private function tryInterfaceMapping(\RepositoryObject $object, $from, $to)
	{
		// Extract the actual definitions.
		$defFrom = $from->getDefinition();
		$defTo = $to->getDefinition();

		// Look for an interface specifier for the $to type.
		$toIntf = null;
		foreach ($defTo->getTypes()->getElements() as $t) {
			if ($t instanceof \Objects\InterfaceType) {
				if ($toIntf !== null) {
					throw new \RuntimeException("Type {$defTo->getId()} has multiple interface type specifiers.");
				}
				$toIntf = $t;
			}
		}
		if ($toIntf === null) {
			return new InvalidType;
		}

		// Check whether the $from type satisifies the $toIntf interface.
		$this->println(2, "Checking whether {$defFrom->getId()} satisfies interface {$toIntf->getId()}", $object->getId());
		foreach ($toIntf->getFuncs()->getElements() as $func) {
			$this->println(3, "- Does {$func->getId()} '{$func->getName()}' exist for @ = {$defFrom->getId()}?", $object->getId());

			// TODO: The following code should move into its own stage which is executed near the BindIdentifiersStage.
			$externals = $this->repository->getImportedNamesForObject($object->getId());
			$funcIds = array();
			foreach ($externals as $externalId => $externalName) {
				if ($externalName == $func->getName()) {
					$funcIds[] = $externalId;
				}
			}
			$this->println(3, "- Potential candidates are ".implode(", ", $funcIds), $object->getId());

			// Check each function candidate individually.
			foreach ($funcIds as $funcId) {
				$this->println(4, "- Checking candidate $funcId", $object->getId());
				$f = $this->repository->getObject($funcId);
				$argsi = $f->getActualType()->getInputs()->getArguments()->getElements();
				$argso = $f->getActualType()->getOutputs()->getArguments()->getElements();
				if (count($argsi) != $func->getInputs()->getCount() || count($argso) != $func->getOutputs()->getCount()) {
					$this->println(5, "  - Input or output argument count not equal", $object->getId());
					continue;
				}
				$match = true;
				foreach ($func->getInputs()->getElements() as $index => $t) {
					if ($t instanceof \Objects\InterfacePlaceholderType) {
						$t = $from;
					}
					$this->println(5, "  - Testing whether candidate input $index is compatible with ".\Type::describe($t), $object->getId());
					if ($t->getDefinition()->getId() != $argsi[$index]->getType()->getDefinition()->getId()) {
						$match = false;
						break;
					}
				}
				if (!$match) continue;
				foreach ($func->getOutputs()->getElements() as $index => $t) {
					if ($t instanceof \Objects\InterfacePlaceholderType) {
						$t = $from;
					}
					$this->println(5, "  - Testing whether candidate output $index is compatible with ".\Type::describe($t), $object->getId());
					if ($t->getDefinition()->getId() != $argso[$index]->getType()->getDefinition()->getId()) {
						$match = false;
						break;
					}
				}
				if (!$match) continue;
				$this->println(5, "  - $funcId is a match!", $object->getId());

				// Create the proper type.
				$imt = new \Objects\InterfaceMappedType;
				$imt->setFromRef($from, $this->repository);
				$imt->setToRef($to, $this->repository);
				$imt->setInterfaceRef($toIntf, $this->repository);
				return $imt;
			}
		}

		return new InvalidType;
	}
}