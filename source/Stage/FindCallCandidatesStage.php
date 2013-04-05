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
			$this->println(1, "Finding candidates for call $name", $object->getId());

			// Traverse the graph looking for any object with this name.
			// TODO: Do this in the future. This would allow us to call
			// variables just like functions.

			// Find functions which are all declared externally.
			$externals = $this->repository->getImportedNamesForObject($object->getId());
			foreach ($externals as $externalId => $externalName) {
				if ($externalName == $name) {
					$array->add($this->makeCandidate($object, $externalId));
					/*$ref = new \RepositoryObjectReference($this->repository);
					$ref->set($externalId);
					$c = new \Objects\CallCandidate;
					$c->setFunc($ref);
					$array->add($c);
					$this->println(2, "Candidate $externalId", $object->getId());*/
				}
			}

			// Store the candidates.
			$object->setCallCandidates($array);
			if (!$object->getCallCandidates()->getCount()) {
				throw new \RuntimeException("Called function '$name' is not known.");
			}

			// Dump the call to the console.
			$this->println(3, $object->describe(), $object->getId());
		}
	}

	private function makeCandidate(\RepositoryObject $object, $id)
	{
		$this->println(2, "Analyzing $id as a candidate", $object->getId());
		$f = $this->repository->getObject($id);
		$c = new \Objects\CallCandidate;
		$c->setFuncRef($f, $this->repository);

		// Wrap the input arguments.
		$args = new \RepositoryObjectArray;
		foreach ($object->getCallArguments()->getArguments()->getElements() as $index => $argument) {
			$this->println(3, "Wrapping argument {$argument->getId()}", $object->getId());
			$ca = new \Objects\CallCandidateArgument;
			$ca->setArgumentRef($argument, $this->repository);
			$args->add($ca);
		}
		$c->setArguments($args);

		return $c;
	}
}