<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class CalculatePossibleTypesStage extends DriverStage
{
	static public $verbosity = 1;

	protected function process(\RepositoryObject $object)
	{
		if (!$object->getRequiredType(false)) {
			$object->setRequiredType(new \Objects\GenericType);
		}
		$this->processChildren($object);
	}

	protected function processChildren(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->processChildren($child);
		}

		// Ignore objects that do not have some form of type interface.
		if (!$object instanceof \Objects\TypeInterface)
			return;

		// Functions, Function Arguments and Function Argument Tuples
		if ($object instanceof \AbstractFunctionArgument && !$object->getPossibleType(false, false)) {
			$t = $object->getTypeExpr()->getEvaluatedType();
			$this->addDependency($object, "typeExpr.evaluatedType");
			$a = new \Objects\FunctionArgumentType;
			$a->setName($object->getName());
			$a->setTypeRef($t, $this->repository);
			$object->setPossibleType($a);
		}
		if ($object instanceof \AbstractFunctionArgumentTuple) {
			$a = new \RepositoryObjectArray($this->repository);
			foreach ($object->getArguments()->getElements() as $argument) {
				$t = $argument->getActualType();
				$a->add(clone $t);
				$this->addDependency($argument, "actualType");
				$this->addDependency($t);
			}
			$t = new \Objects\FunctionArgumentTupleType;
			$t->setArguments($a);
			$object->setPossibleType($t);
		}
		if ($object instanceof \AbstractFunction) {
			$ti = $object->getInputs()->getActualType();
			$to = $object->getOutputs()->getActualType();
			$f = new \Objects\FunctionType;
			$f->setInputs(clone $ti);
			$f->setOutputs(clone $to);
			$object->setPossibleType($f);
			$this->addDependency($object, "inputs.actualType");
			$this->addDependency($object, "outputs.actualType");
			$this->addDependency($ti);
			$this->addDependency($to);
		}

		// For objects that contain a call, iterate through all call candidates
		// and find the union set of the return types.
		if ($object instanceof \Objects\CallInterface) {
			$outputTuples = array();
			foreach ($object->getCallCandidates()->getChildren() as $candidate)
			{
				// Calculate the possible types for each call candidate's arguments.
				foreach ($candidate->getArguments()->getElements() as $index => $argument) {
					$this->println(3, "Working on argument $index = {$argument->getId()}", $object->getId());
					//$argument->setPossibleTypeRef($t->getInputs()->getArguments()->get($index)->getType(), $this->repository);
					$argument->setPossibleTypeRef($object->getCallArguments()->getArguments()->get($index)->getExpr()->getPossibleType(), $this->repository);
				}

				// Fetch the function type this candidate is pointing at.
				$f = $candidate->getFunc();
				$this->addDependency($f, "actualType");
				$t = $f->getActualType(false);
				if (!$t) {
					$tr = $f->getActualType(false, false);
					if ($tr) {
						$this->println(3, "Reference is {$tr->getRefId()}", $object->getId());
						$this->println(3, "Which resolves to {$tr->get()->getId()}", $object->getId());
					}
					$this->println(3, "Skipping candidate {$f->getId()} due to unfinished possible type analysis", $object->getId());
					$candidate->setPossibleType(new \Objects\InvalidType);
					continue;
				}

				// Calculate the possible return type of this candidate.
				// DEBUG: Enforce single return value for now. This will change soon.
				$candidate->setPossibleTypeRef($t->getOutputs()->getArguments()->get(0)->getType(), $this->repository);
				$this->println(3, "Candidate {$f->getId()} possible type = ".\Type::describe($candidate->getPossibleType()), $object->getId());

				// Old stuff...
				$outputTuples[] = $t->getOutputs();
			}

			// Dump the call to the console.
			$this->println(3, $object->describe(), $object->getId());

			$t = \Type::unifyArgumentTuples($outputTuples);
			$this->println(2, "Unified outputs = ".\Type::describe($t), $object->getId());

			// At the moment only single return values are supported, which is why we strip the output arguments.
			if ($t->getTypes()->getCount()) {
				foreach ($t->getTypes()->getElements() as $type) {
					$argc = $type->getArguments()->getCount();
					if ($argc > 1) {
						throw new \RuntimeException("Only single or no return value is supported at the moment. Call {$object->getId()} has unified output type ".\Type::describe($t).".");
					}
					if ($argc == 1) {
						$t = clone $type->getArguments()->get(0)->getType();
					} else {
						$t = null;
					}
					break;
				}
			} else {
				$t = new \Objects\InvalidType;
			}

			$object->setPossibleType($t);
		}

		// General expressions.
		if ($object instanceof \Objects\IdentifierExpr) {
			$target = $object->getBindingTarget();
			if ($target instanceof \AbstractFunctionArgument) {
				$t = $target->getActualType()->getType();
				$object->setPossibleTypeRef($t, $this->repository);
				$this->addDependency($target, "actualType.type");
				//$this->addDependency($t);
			} else {
				$object->setPossibleType(new \Objects\InvalidType);
			}
		}
		if ($object instanceof \Objects\AssignmentExpr) {
			$t = $object->getLhs()->getActualType();
			$object->setPossibleTypeRef($t, $this->repository);
			$this->addDependency($object, "lhs.actualType");
			//$this->addDependency($t);
		}
		if ($object instanceof \Objects\ConstantExpr) {
			$name = null;
			$value = $object->getValue();
			if (preg_match('/\./', $value)) {
				$name = "real";
			} else {
				$name = "int";
			}
			$t = new \RepositoryObjectReference($this->repository);
			$t->set($this->repository->getBuiltinType($name));
			$ct = new \Objects\ConcreteType;
			$ct->setDefinition($t);
			$object->setPossibleType($ct);
		}

		// If the actual type has not yet been calculated, it simply equals the
		// possible type for now.
		if ($object->getActualType(false, false) === null) {
			$this->println(2, "Assigning actualType = @ref possibleType", $object->getId());
			$object->setActualTypeRef($object->getPossibleType(), $this->repository);
		}

		// Show the output of the stage.
		$this->println(1, \Type::describe($object->getPossibleType()), $object->getId());
	}
}