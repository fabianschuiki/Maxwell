<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObjectSerializer
{
	static public function serialize(RepositoryObject $object, $fragment)
	{
		static::println("Serializing $fragment", $object->getId());
		$output = array();

		// Serialize each property individually.
		if (in_array($fragment, $object->getFragmentNames())) {
			$object->{$fragment."_dirty"} = false;

			// Make sure the fragment is loaded. This helps catching early bugs.
			if (!$object->{$fragment."_loaded"}) {
				throw new \RuntimeException("Fragment $fragment of object {$object->getId()} is not loaded.");
			}

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

		// Serialize the tree objects.
		if ($fragment != "tree" && in_array("tree", $object->getFragmentNames())) {
			$properties = $object->getFragment("tree");
			foreach ($properties as $property) {
				$name = $property["name"];
				$getter = "get".ucwords($name);
				$value = $object->$getter();
				if ($value !== null) {
					$output[$name] = static::serialize($value, $fragment);
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
		if ($value instanceof RepositoryNodeObject) {
			// If the value is inside the tree fragment, only serialize the given fragment.
			// Otherwise serialize all fragments at once.
			if ($value->isInTree()) {
				$output = static::serialize($value, $fragment);
			} else {
				$output = array();
				foreach ($value->getFragmentNames() as $name) {
					$output = array_merge($output, static::serialize($value, $name));
				}
			}
			$output["class"] = $value->getClass();
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
		static::println("Unserializing $fragment", $object->getId());

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

	static private function println($ln, $info = null)
	{
		Log::println($ln, get_class(), $info);
	}
}