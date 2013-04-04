<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class CalculateRequiredTypesStage extends DriverStage
{
	static public $verbosity = 0;

	protected function process(\RepositoryObject $object)
	{
		// Assignments require the rhs to match the lhs.
		if ($object instanceof \Objects\AssignmentExpr) {
			$object->getRhs()->setRequiredType($object->getLhs()->getPossibleType());
		}

		// For objects that contain a call, the procedure is similar to the one performed in the CalculatePossibleTypesStage. The input argument tuples are unified and then assigned as a requirement to each call argument individually.
		if ($object instanceof \Objects\CallInterface) {
			$inputTuples = array();
			foreach ($object->getCallCandidates()->getChildren() as $candidate) {
				$f = $candidate->getFunc()->get();
				$t = $f->getActualType(false);
				if (!$t)
					$t = $f->getPossibleType();
				$inputTuples[] = $t->getInputs();
			}
			$t = \Type::unifyArgumentTuples($inputTuples);
			$this->println(2, "Unified inputs = ".\Type::describe($t), $object->getId());

			// Assign each call argument the respective set of types that are possible.
			foreach ($object->getCallArguments()->getArguments()->getElements() as $index => $argument) {
				$a = new \RepositoryObjectArray;
				foreach ($t->getTypes()->getElements() as $tuple) {
					$ta = $tuple->getArguments()->get($index, false);
					if ($ta !== null) {
						$a->add($ta->getType());
					}
				}
				if ($a->getCount() > 0) {
					$s = new \Objects\TypeSet;
					$s->setTypes($a);
					$s = \Type::simplifySet($s);
					$argument->getExpr()->get()->setRequiredType($s);
				} else {
					$argument->getExpr()->get()->setRequiredType(new \Objects\InvalidType);
				}
			}
		}

		// Each child that does not have a type requirement has its required type set to the generic type.
		foreach ($object->getChildren() as $child) {
			$this->process($child);
			if ($child instanceof \Objects\TypeInterface) {
				if ($child->getRequiredType(false) === null) {
					$child->setRequiredType(new \Objects\GenericType);
				}
				$this->println(1, \Type::describe($child->getRequiredType()), $child->getId());
			}
		}
	}
}