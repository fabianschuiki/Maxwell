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

		// Ignore objects that do not have some form of type interface.
		if (!$object instanceof \Objects\TypeInterface)
			return;

		// Functions, Function Arguments and Function Argument Tuples
		if ($object instanceof \AbstractFunctionArgument) {
			//$this->println(1, "Argument {$object->getId()}", $object->getId());
			$a = new \Objects\FunctionArgumentType;
			$a->setName($object->getName());
			$a->setType($object->getTypeExpr()->getEvaluatedType());
			$object->setPossibleType($a);
			//$object->setPossibleType($object->getTypeExpr()->getEvaluatedType());
		}
		if ($object instanceof \AbstractFunctionArgumentTuple) {
			//$this->println(1, "Argument Tuple {$object->getId()}", $object->getId());
			$a = new \RepositoryObjectArray($this->repository);
			foreach ($object->getArguments()->getElements() as $argument) {
				$a->add($argument->getPossibleType());
			}
			$t = new \Objects\FunctionArgumentTupleType;
			$t->setArguments($a);
			$object->setPossibleType($t);
		}
		if ($object instanceof \AbstractFunction) {
			//$this->println(1, "Function {$object->getId()}", $object->getId());
			$f = new \Objects\FunctionType;
			$f->setInputs($object->getInputs()->getPossibleType());
			$f->setOutputs($object->getOutputs()->getPossibleType());
			$object->setPossibleType($f);
		}

		// For objects that contain a call, iterate through all call candidates
		// and find the union set of the return types.
		if ($object instanceof \Objects\CallInterface) {
			$outputTuples = array();
			foreach ($object->getCallCandidates()->getChildren() as $candidate) {
				$t = $candidate->getFunc()->get()->getPossibleType();
				$outputTuples[] = $t->getOutputs();
			}
			$t = $this->unifyArgumentTupleTypes($outputTuples);
			$this->println(2, "unified tuple = ".\Type::describe($t), $object->getId());

			// At the moment only single return values are supported, which is why we strip the output arguments.
			foreach ($t->getTypes()->getElements() as $type) {
				$argc = $type->getArguments()->getCount();
				if ($argc > 1) {
					throw new \RuntimeException("Only single or no return value is supported at the moment. Call {$object->getId()} has unified output type ".\Type::describe($t).".");
				}
				if ($argc == 1) {
					$t = $type->getArguments()->get(0)->getType();
				} else {
					$t = null;
				}
				break;
			}

			$object->setPossibleType($t);
		}

		// General expressions.
		if ($object instanceof \Objects\IdentifierExpr) {
			$target = $object->getBindingTarget()->get();
			if ($target instanceof \AbstractFunctionArgument) {
				$object->setPossibleType($target->getPossibleType()->getType());
			}
		}
		if ($object instanceof \Objects\AssignmentExpr) {
			$object->setPossibleType($object->getLhs()->getPossibleType());
		}

		// Show the output of the stage.
		$this->println(1, \Type::describe($object->getPossibleType(false)), $object->getId());
	}

	private function unifyArgumentTupleTypes(array $tuples)
	{
		$unified = array(); // unified tuples indexed by their lengths
		foreach ($tuples as $tuple) {
			$l = $tuple->getArguments()->getCount();
			if (!isset($unified[$l])) {
				$u = new \Objects\FunctionArgumentTupleType;
				$u->setArguments(new \RepositoryObjectArray);
				$unified[$l] = $u;
			}
			$unifiedArguments = $u->getArguments();
			foreach ($tuple->getArguments()->getElements() as $index => $argument) {
				$ua = $unifiedArguments->get($index, false);
				if (!$ua) {
					$unifiedArguments->set($index, $argument);
				} else if ($ua->getType() instanceof \Objects\TypeSet) {
					$ua->getType()->getTypes()->add($argument);
				} else {
					$a = new \RepositoryObjectArray;
					$a->add($ua->getType());
					$a->add($argument->getType());
					$s = new \Objects\TypeSet;
					$s->setTypes($a);
					$ua->setType($s);
				}
			}
		}

		// Transform the array of unified tuples into a set of types.
		$a = new \RepositoryObjectArray;
		foreach ($unified as $u) {
			$a->add($u);
		}
		$s = new \Objects\TypeSet;
		$s->setTypes($a);
		return $s;
	}
}