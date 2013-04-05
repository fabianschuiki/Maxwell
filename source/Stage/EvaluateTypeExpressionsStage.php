<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class EvaluateTypeExpressionsStage extends DriverStage
{
	static public $verbosity = 99;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}
		if ($object instanceof \Objects\TypeExpr)
		{
			if (!$object->getEvaluatedType(false)) {
				$result = $this->processExpr($object->getExpr());
				$object->setEvaluatedType($result);
				$this->println(1, "evaluated to ".get_class($result), $object->getId());
			}
		}
	}

	/**
	 * Converts the given object into a type object or throws an exception if
	 * the conversion is not possible.
	 */
	protected function processExpr(\RepositoryObject $object)
	{
		if ($object instanceof \Objects\IdentifierExpr) {
			$def = new \Objects\ConcreteType;
			$def->setDefinitionRef($object->getBindingTarget(true, false), $this->repository);
			return $def;
		}
		throw new \InvalidArgumentException("Unable to evaluate {$object->getId()} (".get_class($object).") in type expression.");
	}
}