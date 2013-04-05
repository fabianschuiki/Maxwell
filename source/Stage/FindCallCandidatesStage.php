<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class FindCallCandidatesStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		// Everything that has a call interface.
		if ($object instanceof \Objects\CallInterface)
		{
			// Do not perform any search if there are candidates around already.
			//if ($object->getCallCandidates(false))
			//	return;

			// Create the array that will hold the candidates.
			$array = new \RepositoryObjectArray;
			$name = $object->getCallName();

			// Traverse the graph looking for any object with this name.
			// TODO: Do this in the future. This would allow us to call
			// variables just like functions.

			// Find functions which are all declared externally.
			$externals = $this->repository->getImportedNamesForObject($object->getId());
			foreach ($externals as $externalId => $externalName) {
				if ($externalName == $name) {
					$ref = new \RepositoryObjectReference($this->repository);
					$ref->set($externalId);
					$c = new \Objects\CallCandidate;
					$c->setFunc($ref);
					$array->add($c);
					$this->println(2, "Candidate $externalId", $object->getId());
				}
			}

			// Store the candidates.
			$object->setCallCandidates($array);
			if (!count($object->getCallCandidates()->getElements())) {
				$this->println(2, "Called function '$name' is not known", $object->getId());
			}

			// Dump the call to the console.
			$this->println(3, $object->describe(), $object->getId());
		}
	}
}