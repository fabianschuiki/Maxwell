<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class SelectCallCandidateStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}
		if (!$object instanceof \Objects\CallInterface)
			return;

		// Extract the feasible candidates.
		$candidates = array_filter($object->getCallCandidates()->getElements(), function(\Objects\CallCandidate $c) {
			return $c->getFeasible();
		});

		// Use whatever feasible candidates we got back.
		if (count($candidates) == 0) {
			throw new \RuntimeException("Call {$object->getId()} has no feasible out of ".count($object->getCallCandidates()->getElements())." candidates.");
		} else if (count($candidates) > 1) {
			throw new \RuntimeException("Call {$object->getId()} is ambiguous.");
		} else {
			$object->setSelectedCallCandidate(array_pop($candidates));
		}

		// Show the output of the stage.
		$this->println(1, "Selected call candidate ".\Type::describe($object->getSelectedCallCandidate()->getFunc()->get()->getActualType()), $object->getId());
	}
}