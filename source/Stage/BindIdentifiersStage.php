<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class BindIdentifiersStage extends DriverStage
{
	static public $verbosity = 20;

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
			$current = $object->getGraphPrev()->get();
			$target = null;
			$name = $object->getName();
			while ($current)
			{
				// Bind to function arguments.
				if ($current instanceof \Objects\FunctionArgument) {
					if ($current->getName() == $name) {
						$target = $current;
						break;
					}
				}

				// Bind to variable definitions.
				if ($current instanceof \Objects\VariableExpr) {
					if ($current->getName() == $name) {
						$target = $current;
						break;
					}
				}

				$current = $current->getGraphPrev()->get();
			}

			// Check whether we've found something.
			if (!$target) {
				$this->println(1, "No object named '$name' found", $object->getId());
			} else {
				$this->println(1, "Binding to {$target->getId()}");
			}

			// Store the binding.
			$ref->set($target);
			$object->setBindingTarget($target !== null ? $ref : null);
		}
	}
}
