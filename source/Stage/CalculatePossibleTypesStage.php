<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class CalculatePossibleTypesStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		// For objects that contain a call, iterate through all call candidates
		// and find the union set of the return types.
		if ($object instanceof \Objects\CallInterface) {
			foreach ($object->getCallCandidates()->getChildren() as $candidate) {
				$this->println(1, "Candidate {$candidate->getId()}", $object->getId());
			}
		}
	}
}