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
			$t = $object->getLhs()->getPossibleType();
			$this->addDependency($t);
			$object->getRhs()->setRequiredType(clone $t);
		}

		// Variables require the initial expression to match the variable type.
		if ($object instanceof \Objects\VariableDefinitionExpr) {
			$ie = $object->getInitialExpr();
			$te = $object->getTypeExpr();
			if (!$ie instanceof \Objects\NullObject) {
				if (!$te instanceof \Objects\NullObject) {
					$t = $te->getEvaluatedType();
					$ie->setRequiredTypeRef($t, $this->repository);
					$this->addDependency($object, "typeExpr.evaluatedType");
				} else {
					$ie->setRequiredType(new \Objects\GenericType);
				}
			}
		}

		// For objects that contain a call, the procedure is similar to the one performed in the CalculatePossibleTypesStage. The input argument tuples are unified and then assigned as a requirement to each call argument individually.
		if ($object instanceof \Objects\CallInterface) {
			$inputTuples = array();
			$inputTypes = array();
			foreach ($object->getCallCandidates()->getChildren() as $candidate)
			{
				// Fetch the function type this candidate is pointing at.
				$f = $candidate->getFunc();
				$this->addDependency($f, "actualType");
				$t = $f->getActualType();

				// Calculate the required types for each call candidate's arguments.
				foreach ($candidate->getArguments()->getElements() as $index => $argument) {
					$rt = $t->getInputs()->getArguments()->get($index)->getType();
					$argument->setRequiredTypeRef($rt, $this->repository);
					$inputTypes[$index][] = $rt;
				}

				// Calculate the required return type of this candidate.
				$candidate->setRequiredTypeRef($object->getRequiredType(), $this->repository);
			}

			// Dump the call to the console.
			//$this->println(3, $object->describe(), $object->getId());

			// For each call argument come up with a set of required types.
			foreach ($object->getCallArguments()->getArguments()->getElements() as $index => $argument) {
				if (isset($inputTypes[$index])) {
					$a = new \RepositoryObjectArray;
					foreach ($inputTypes[$index] as $type) {
						$a->add(clone $type);
					}
					$s = new \Objects\TypeSet;
					$s->setTypes($a);
					$t = \Type::simplifySet($s);
				} else {
					$t = new \Objects\InvalidType;
				}
				$this->println(3, "Calculated type set for argument $index to be ".\Type::describe($t), $object->getId());
				$argument->getExpr()->setRequiredType(clone $t);
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