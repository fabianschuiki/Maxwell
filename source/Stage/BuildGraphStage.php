<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;
use Objects\GraphInterface;

/**
 * Builds a directed acyclic graph in the objects' graph fragment.
 */
class BuildGraphStage extends DriverStage
{
	static public $verbosity = 1;

	protected function process(\RepositoryObject $object)
	{
		$last = $this->processCarry($object, null);
		$this->println(1, "last = ".($last ? $last->getId() : "<none>"));
	}

	protected function processCarry(\RepositoryObject $object, $carry)
	{
		if ($object instanceof GraphInterface) {
			$this->println(1, "graphPrev = ".($carry ? $carry->getId() : "<none>"), $object->getId());
			$ref = $object->getGraphPrev(false);
			if (!$ref) {
				$ref = new \RepositoryObjectReference($this->repository);
			}
			$ref->set($carry);
			$object->setGraphPrev($ref);
			$previous = $object;
		} else {
			$previous = $carry;
		}
		foreach ($object->getChildren() as $child) {
			$previous = $this->processCarry($child, $previous);
		}
		return $previous;
	}
}