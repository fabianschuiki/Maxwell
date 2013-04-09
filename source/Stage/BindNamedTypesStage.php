<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class BindNamedTypesStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		if ($object instanceof \Objects\NamedType)
		{
			// Do nothing if the name is already bound.
			if ($object->getDefinition(false, false))
				return;
			$name = $object->getName();
			$this->println(2, "Binding type name $name", $object->getId());

			// Traverse the graph lookign for any type with this name.
			$current = $object->getGraphPrev();
			$target = null;
			while ($current) {
				if ($current instanceof \Objects\TypeDefinition) {
					if ($current->getName() == $name) {
						$target = $current;
						break;
					}
				}
				$current = $current->getGraphPrev();
			}

			// Find an external entity if nothing has been found so far.
			if ($target === null) {
				$externals = $this->repository->getImportedNamesForObject($object->getId());
				foreach ($externals as $externalId => $externalName) {
					if ($externalName == $name) {
						$target = $externalId;
					}
				}
			}

			//Check whether we've found something.
			if ($target === null) {
				throw new \RuntimeException("No type named '$name' found for {$object->getId()}.");
			} else {
				$this->println(1, "Bound type name $name to ".(is_object($target) ? $target->getId() : $target), $object->getId());
			}

			// Store the binding.
			$ref = new \RepositoryObjectReference($this->repository);
			$ref->set($target);
			$object->setDefinition($ref);
		}
	}
}