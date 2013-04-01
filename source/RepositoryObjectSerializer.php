<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObjectSerializer
{
	static public function serialize(RepositoryObject $object, $fragment)
	{
		$output = array();

		// Serialize each property.
		if (in_array($fragment, $object->getFragmentNames())) {
			$properties = $object->getFragment($fragment);
			foreach ($properties as $property) {
				$name = $property["name"];
				$getter = "get".ucwords($name);
				$value = $object->$getter();
				if ($value !== null) {
					$output[$name] = static::serializeValue($value, $fragment);
				}
			}
		}

		// Serialize the object tree.
		if (in_array("tree", $object->getFragmentNames())) {
			$properties = $object->getFragment("tree");
			foreach ($properties as $property) {
				echo "$fragment : $name\n";
				$name = $property["name"];
				$getter = "get".ucwords($name);
				$value = $object->$getter();
				if ($value instanceof RepositoryObject) {
					$a = static::serializeValue($value, $fragment);
					if ($a) $output[$name] = $a;
				}
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
				$value = static::unserializeValue($input->$name, $fragment);
				$object->$setter($value);
			}
		}

		// Unserialize the objects tree.
		$properties = $object->getFragment("tree");
		foreach ($properties as $property) {
			$name = $property["name"];
			$setter = "set".ucwords($name);
			$getter = "get".ucwords($name);
			if (isset($input->$name)) {
				$obj = $object->$getter();
				if (!$obj) {
					if (!isset($input->$name->id) || !isset($input->$name->class)) {
						throw new \InvalidArgumentException("Unable to unserialize object $name lacking id and/or class.");
					}
					$id = $input->$name->id;
					$class = "\\Objects\\".$input->$name->class;
					$obj = new $class($object->getRepository(), $id);
					$object->$setter($obj);
				}
				$obj->{$fragment."_loaded"} = true;
				static::unserialize($obj, $fragment, $input->$name);
			}
		}
	}

	static private function serializeValue($value, $fragment)
	{
		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// RepositoryObjects require a more elaborate procedure.
		if ($value instanceof RepositoryObject) {
			$output = static::serialize($value, $fragment);
			$output["class"] = $value->getClass();
			$output["id"] = $value->getId();
			return $output;
		}

		// Complain about the input value now since we're unable to process it.
		throw new \InvalidArgumentException("Unable to serialize value ".get_class($value).".");
	}

	static private function unserializeValue($value, $fragment)
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