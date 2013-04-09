<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class CalculatePossibleTypesStage extends DriverStage
{
	static public $verbosity = 0;

	protected function process(\RepositoryObject $object)
	{
		if ($object instanceof \Objects\TypeInterface && !$object->getRequiredType(false)) {
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
		if ($object instanceof \Objects\CallInterface)
		{
			$outputTypes = new \RepositoryObjectArray;
			foreach ($object->getCallCandidates()->getChildren() as $candidate)
			{
				// Calculate the possible types for each call candidate's arguments.
				foreach ($candidate->getArguments()->getElements() as $index => $argument) {
					$argument->setPossibleTypeRef($object->getCallArguments()->getArguments()->get($index)->getExpr()->getPossibleType(), $this->repository);
				}

				// Fetch the function type this candidate is pointing at.
				$f = $candidate->getFunc();
				$this->addDependency($f, "actualType");
				$t = $f->getActualType(false);
				if (!$t) {
					$this->println(3, "Skipping candidate {$f->getId()} since actualType is null", $object->getId());
					$candidate->setPossibleType(new \Objects\InvalidType);
					continue;
				}

				// Calculate the possible return type of this candidate.
				// DEBUG: Enforce single return value for now. This will change soon.
				$candidate->setPossibleTypeRef($t->getOutputs()->getArguments()->get(0)->getType(), $this->repository);
				$this->println(3, "Candidate {$f->getId()} possible type = ".\Type::describe($candidate->getPossibleType()), $object->getId());

				// Keep the possible output type around.
				$outputTypes->add(clone $candidate->getPossibleType());
			}

			// Dump the call to the console.
			//$this->println(3, $object->describe(), $object->getId());

			// Assemble the outputs into a set.
			if ($outputTypes->getCount() > 0) {
				$outputSet = new \Objects\TypeSet;
				$outputSet->setTypes($outputTypes);
				$outputSet = \Type::simplifySet($outputSet);
				$this->println(2, "Union candidate output types = ".\Type::describe($outputSet), $object->getId());
				$object->setPossibleType(clone $outputSet);
			} else {
				$object->setPossibleType(new \Objects\InvalidType);
			}
		}

		// General expressions.
		if ($object instanceof \Objects\IdentifierExpr) {
			$target = $object->getBindingTarget();

			// Look for assumptions in the graph that point at this object.
			$assumedType = null;
			$current = $object;
			while ($current) {
				if ($current instanceof \Objects\AssumerInterface) {
					$asm = $current->getAssumptions(false);
					if ($asm) {
						foreach ($asm->getElements() as $assumption) {
							if ($assumption->getTarget()->getBindingTarget() == $target) {
								$this->println(2, "Considering {$assumption->getId()}", $object->getId());
								$assumedType = $assumption->getAssumption()->getEvaluatedType();
								$this->addDependency($assumption, "assumption.evaluatedType");
							}
						}
					}
				}
				$current = $current->getGraphPrev();
			}

			$t = null;
			if ($target instanceof \AbstractFunctionArgument) {
				$t = $target->getActualType()->getType();
			} else if ($target instanceof \Objects\VariableDefinitionExpr) {
				$t = $target->getActualType();
			}

			if ($t) {
				if ($assumedType) {
					// check $assumedType->isSubtypeOf($t)
					$this->println(3, "Assuming type to be ".\Type::describe($assumedType)." instead of ".\Type::describe($t), $object->getId());
					$t = $assumedType;
				}
				$object->setPossibleTypeRef($t, $this->repository);
				$this->addDependency($target, "actualType.type");
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
		if ($object instanceof \Objects\VariableDefinitionExpr) {
			/*$te = $object->getTypeExpr();
			$t = null;
			if (!$te instanceof \Objects\NullObject) {
				$t = $te->getEvaluatedType();
				$this->addDependency($object, "typeExpr.evaluatedType");
			} else {
				$ti = $object->getInitialExpr();
				if (!$ti instanceof \Objects\NullObject) {
					$t = $ti->getActualType();
					$this->addDependency($object, "initialExpr.actualType");
				}
			}
			if ($t) {
				$object->setPossibleTypeRef($t, $this->repository);
			} else {
				$object->setPossibleType(new \Objects\InvalidType);
			}*/
			$this->addDependency($object, "type");
			$object->setPossibleTypeRef($object->getType(), $this->repository);
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