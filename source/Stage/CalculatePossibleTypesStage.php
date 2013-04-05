<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class CalculatePossibleTypesStage extends DriverStage
{
	static public $verbosity = 1;

	protected function process(\RepositoryObject $object)
	{
		$object->setRequiredType(new \Objects\GenericType);
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
		if ($object instanceof \AbstractFunctionArgument) {
			$t = $object->getTypeExpr()->getEvaluatedType();
			$this->addDependency($t);
			$a = new \Objects\FunctionArgumentType;
			$a->setName($object->getName());
			$a->setType(clone $t);
			$object->setPossibleType($a);
		}
		if ($object instanceof \AbstractFunctionArgumentTuple) {
			$a = new \RepositoryObjectArray($this->repository);
			foreach ($object->getArguments()->getElements() as $argument) {
				$t = $argument->getPossibleType();
				$this->addDependency($t);
				$a->add(clone $t);
			}
			$t = new \Objects\FunctionArgumentTupleType;
			$t->setArguments($a);
			$object->setPossibleType($t);
		}
		if ($object instanceof \AbstractFunction) {
			$ti = $object->getInputs()->getPossibleType();
			$to = $object->getOutputs()->getPossibleType();
			$this->addDependency($ti);
			$this->addDependency($to);
			$f = new \Objects\FunctionType;
			$f->setInputs(clone $ti);
			$f->setOutputs(clone $to);
			$object->setPossibleType($f);
		}

		// For objects that contain a call, iterate through all call candidates
		// and find the union set of the return types.
		if ($object instanceof \Objects\CallInterface) {
			$outputTuples = array();
			foreach ($object->getCallCandidates()->getChildren() as $candidate) {
				$f = $candidate->getFunc();
				$this->addDependency($candidate);
				$t = $f->getActualType(false);
				if (!$t)
					$t = $f->getPossibleType();
				$this->addDependency($t);
				$outputTuples[] = $t->getOutputs();
			}
			$t = \Type::unifyArgumentTuples($outputTuples);
			$this->println(2, "Unified outputs = ".\Type::describe($t), $object->getId());

			// At the moment only single return values are supported, which is why we strip the output arguments.
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

			$object->setPossibleType($t);
		}

		// General expressions.
		if ($object instanceof \Objects\IdentifierExpr) {
			$target = $object->getBindingTarget();
			if ($target instanceof \AbstractFunctionArgument) {
				$t = $target->getPossibleType()->getType();
				$this->addDependency($t);
				$object->setPossibleType(clone $t);
			} else {
				$object->setPossibleType(new \Objects\InvalidType);
			}
		}
		if ($object instanceof \Objects\AssignmentExpr) {
			$t = $object->getLhs()->getPossibleType();
			$this->addDependency($t);
			$object->setPossibleType(clone $t);
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

		// Show the output of the stage.
		$this->println(1, \Type::describe($object->getPossibleType()), $object->getId());
	}
}