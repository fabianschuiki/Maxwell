<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class NarrowCallCandidatesStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		if ($object instanceof \Objects\CallInterface) {
			foreach ($object->getCallCandidates()->getElements() as $candidate) {
				/*if ($candidate->getFeasible(false) === false)
					continue;*/
				$candidateType = $candidate->getFunc()->getActualType();
				$this->println(2, "Investigating candidate ".\Type::describe($candidateType), $object->getId());

				// Check the call arguments.
				$feasible = true;
				foreach ($candidate->getArguments()->getElements() as $index => $argument) {
					/*$candType = $candidateType->getInputs()->getArguments()->get($index)->getType();
					$callType = $argument->getExpr()->getActualType();
					$this->addDependency($callType);
					$this->println(2, "Matching input ".\Type::describe($callType)." against ".\Type::describe($candType), $argument->getId());
					if (!\Type::equal($candType, $callType)) {
						$feasible = false;
						break;
					}*/
					$at = $argument->getActualType();
					$this->println(3, "Argument {$argument->getId()} has actual type ".\Type::describe($at), $object->getId());
					if ($at instanceof \Objects\InvalidType) {
						$feasible = false;
					}
				}

				// Check the return type.
				if ($feasible === true) {
					/*$callType = $object->getRequiredType();
					$candOutArgs = $candidateType->getOutputs()->getArguments();
					if ($candOutArgs->getCount() == 1) {
						$candOutArg = $candOutArgs->get(0)->getType();
						$this->addDependency($candOutArg);
						$this->println(2, "Matching output ".\Type::describe($callType)." against ".\Type::describe($candOutArg), $object->getId());
						$feasible = \Type::equal($callType, $candOutArg);
					}*/
					$at = $candidate->getActualType();
					$this->println(3, "Return type of {$candidate->getId()} has actual type ".\Type::describe($at), $object->getId());
					if ($at instanceof \Objects\InvalidType) {
						$feasible = false;
					}
				}

				// Store the data.
				$this->println(1, "Candidate ".\Type::describe($candidateType)." is ".($feasible ? "feasible" : "not feasible"), $object->getId());
				$candidate->setFeasible($feasible);
			}
		}
	}
}