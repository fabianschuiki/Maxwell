<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class BindIdentifiersStage extends DriverStage
{
	static public $verbosity = 1;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}
		if ($object instanceof \Objects\IdentifierExpr)
		{
			// Fetch the reference to the currently bound target.
			$ref = $object->getBindingTarget(false);
			if ($ref) return;
			$ref = new \RepositoryObjectReference($this->repository);

			// Traverse the graph looking for any object with this name.
			$current = $object->getGraphPrev();
			$target = null;
			$name = $object->getName();
			$consulted = array();
			while ($current)
			{
				// Bind to function arguments.
				if ($current instanceof \Objects\FunctionArgument) {
					if ($current->getName() == $name) {
						$target = $current->getId();
						break;
					}
				}

				// Bind to variable definitions.
				if ($current instanceof \Objects\VariableDefinitionExpr) {
					if ($current->getName() == $name) {
						$target = $current->getId();
						break;
					}
				}

				$consulted[] = $current->getId();
				$current = $current->getGraphPrev();
			}

			// Find an external entity.
			if (!$target) {
				$externals = $this->repository->getImportedNamesForObject($object->getId());
				foreach ($externals as $externalId => $externalName) {
					if ($externalName == $name) {
						$target = $externalId;
					}
				}
			}

			// Check whether we've found something.
			if (!$target) {
				$this->println(1, "No object named '$name' found", $object->getId());
				throw new \RuntimeException("No object named '$name' found for identifier {$object->getId()}. Consulted: ".print_r($consulted, true));
			} else {
				$this->println(1, "Binding to $target", $object->getId());
			}

			// Store the binding.
			$ref->set($target);
			$object->setBindingTarget($ref);
		}
	}
}
