<?php
/* Copyright © 2013 Fabian Schuiki */
namespace Stage;
use DriverStage;

class BindIdentifiersStage extends DriverStage
{
	static public $verbosity = 1;

	protected function process(\RepositoryObject $object)
	{
		foreach ($object->getChildren() as $child) {
			$this->process($child);
		}

		//$this->println("Processing ".get_class($object), $object->getId());
		if ($object instanceof \Objects\IdentifierExpr) {
			$this->println(1, "Binding '{$object->getName()}' {$object->getId()}");
			$existing = $object->getBindingDebug(false);
			if ($existing) {
				$this->println(1, "- Already contains '$existing'");
			} else {
				$object->setBindingDebug("<target {$object->getName()}>");
			}
		}
	}
}
