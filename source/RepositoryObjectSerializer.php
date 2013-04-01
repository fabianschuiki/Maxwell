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

	/**
	 * Treats the given input object as the serialized version of the fragment
	 * $fragment of the given object $object and unserializes its contents into
	 * $object.
	 */
	static public function unserialize(RepositoryObject $object, $fragment, \stdClass $input)
	{
		echo "Unserializing $fragment of {$object->getClass()}\n";

		// Unserialize each property individually.
		if (in_array($fragment, $object->getFragmentNames())) {
			$object->{$fragment."_loaded"} = true;
			$properties = $object->getFragment($fragment);
			foreach ($properties as $property) {
				$name = $property["name"];
				$setter = "set".ucwords($name);
				if (isset($input->$name)) {
					$value = static::unserializeValue($input->$name, $fragment);
					$object->$setter($value, false);
				}
			}
		}

		// Unserialize the tree objects.
		if ($fragment != "tree" && in_array("tree", $object->getFragmentNames())) {
			$properties = $object->getFragment("tree");
			foreach ($properties as $property) {
				$object->{$fragment."_loaded"} = true;
				$name = $property["name"];
				$getter = "get".ucwords($name);
				if (isset($input->$name)) {
					echo " - also loading $fragment for $name\n";
					$obj = $object->$getter();
					if (!$obj) {
						throw new \RuntimeException("Object ID {$object->getId()} is expected to have at least a bare version of $name which is not the case. Maybe the tree fragment was not properly loaded?");
					}
					static::unserialize($obj, $fragment, $input->$name);
				}
			}
		}
	}

	/**
	 * Unserializes the given value and returns the resulting object or value.
	 * This function will produce bare RepositoryObject instances where
	 * appropriate.
	 */
	static private function unserializeValue($value, $fragment)
	{
		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// Some object.
		if (is_object($value)) {
			if (!isset($value->class)) {
				throw new \InvalidArgumentException("Object value is missing 'class' field required for unserialization: ".print_r($value, true));
			}
			$class = "\\Objects\\".$value->class;
			echo "Will instantiate bare $class\n";
			$obj = new $class;

			// Unserialize the object's tree if we're currently unserializing the tree fragment.
			// Otherwise unserialize all fragments of the object as it is contained entirely here.
			if ($fragment == "tree") {
				static::unserialize($obj, "tree", $value);
			} else {
				foreach ($obj->getFragmentNames() as $name) {
					static::unserialize($obj, $name, $value);
				}
			}

			return $obj;
		}

		// Complain about the input as we obviously can't process it.
		throw new \InvalidArgumentException("Unable to unserialize value: ".print_r($value, true));
	}
}