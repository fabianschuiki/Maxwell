<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class ConfigureAssumptionStatementsStage extends DriverStage
{
	static public $verbosity = 0;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		// Move the assumptions made in AssumeStmt objects into their respective assumptions property.
		if ($object instanceof \Objects\AssumeStmt) {
			$a = new \Objects\Assumption;
			$a->setTargetRef($object->getTarget(), $this->repository);
			$a->setAssumptionRef($object->getAssumption(), $this->repository);
			$b = new \RepositoryObjectArray;
			$b->add($a);
			$object->setAssumptions($b);
		}
	}
}