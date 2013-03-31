<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObjectSerializer
{
	static public function serialize(RepositoryObject $object, $fragment)
	{
		// Fetch the properties that have to be serialized.
		$properties = $object->getFragment($fragment);

		// Serialize each property individually.
		$output = array();
		foreach ($properties as $property) {
			$name = $property["name"];
			$getter = "get".ucwords($name);
			$value = $object->$getter();
			if ($value !== null) {
				$output[$name] = static::serializeValue($value);
			}
		}

		return $output;
	}

	static public function unserialize(RepositoryObject $object, $fragment, \stdClass $input)
	{
		// Fetch the properties we can expect from this object.
		$properties = $object->getFragment($fragment);

		// Unserialize each property individually.
		foreach ($properties as $property) {
			$name = $property["name"];
			$setter = "set".ucwords($name);
			if (isset($input->$name)) {
				$value = static::unserializeValue($input->$name);
				$object->$setter($value);
			}
		}
	}

	static private function serializeValue($value)
	{
		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// RepositoryObjects require a more elaborate procedure.
		if ($value instanceof RepositoryObject) {
			$output = array();
			foreach ($value->getFragmentNames() as $name) {
				$output = array_merge($output, static::serialize($value, $name));
			}
			$output["class"] = $value->getClass();
			$output["id"] = $value->getId();
			return $output;
		}

		// Complain about the input value now since we're unable to process it.
		throw new \InvalidArgumentException("Unable to serialize value ".get_class($value).".");
	}

	static private function unserializeValue($value)
	{
		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// Objects may represent any form of object.
		//if (is_object($value))

		// Complain about the input as we obviously can't process it.
		throw new \InvalidArgumentException("Unable to unserialize value: ".print_r($value, true));
	}
}