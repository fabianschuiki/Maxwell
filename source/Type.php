<?php
/* Copyright © 2013 Fabian Schuiki */

/**
 * Class containing helper functions for dealing with type objects.
 */
class Type
{
	static public function describe($object)
	{
		// DEBUG: remove this later!!!
		if ($object === null) return "<null>";

		if ($object instanceof \Objects\ConcreteType) {
			return "@".$object->getDefinition()->getId();
		}
		if ($object instanceof \Objects\FunctionArgumentType) {
			return static::describe($object->getType())." ".$object->getName();
		}
		if ($object instanceof \Objects\FunctionArgumentTupleType) {
			$a = array();
			foreach ($object->getArguments()->getElements() as $argument) {
				$a[] = static::describe($argument);
			}
			return "(".implode(", ", $a).")";
		}
		if ($object instanceof \Objects\FunctionType) {
			return static::describe($object->getInputs())." -> ".static::describe($object->getOutputs());
		}
		if ($object instanceof \Objects\TypeSet) {
			$a = array();
			foreach ($object->getTypes()->getElements() as $t) {
				$a[] = static::describe($t);
			}
			return "{".implode(", ", $a)."}";
		}

		// Seems like we're unable to handle the object.
		throw new \InvalidArgumentException("Unable to descibe object as type.");
	}
}