<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

/**
 * Configures the "call" fragment for entities that have one.
 */
class ConfigureCallsStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		// Binary operators.
		if ($object instanceof \Objects\BinaryOperatorExpr)
		{
			if ($object->getCallName(false) === null || $object->getCallArguments(false) === null) {
				$object->setCallName($object->getOperator());
				
				// Create references to the left and right hand side.
				$rlhs = new \RepositoryObjectReference($this->repository);
				$rlhs->set($object->getLhs());
				$rrhs = new \RepositoryObjectReference($this->repository);
				$rrhs->set($object->getRhs());

				// Create two call arguments.
				$argl = new \Objects\CallArgument;
				$argl->setExpr($rlhs);
				$argr = new \Objects\CallArgument;
				$argr->setExpr($rrhs);

				// Create the call tuple.
				$a = new \RepositoryObjectArray;
				$a->set(0, $argl);
				$a->set(1, $argr);
				$args = new \Objects\CallArgumentTuple;
				$args->setArguments($a);
				$object->setCallArguments($args);
			}
		}
	}
}