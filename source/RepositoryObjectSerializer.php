<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObjectSerializer
{
	protected $repository;

	public function __construct(Repository $repo)
	{
		$this->repository = $repo;
	}

	public function serialize(RepositoryObject $object, $fragment)
	{
		$this->println(0, "Serializing $fragment", $object->getId());

		// Array objects are a special case.
		if ($object instanceof RepositoryObjectArray) {
			return $this->serializeValue($object, $fragment);
		}

		// Otherwise produce regular output.
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
				$value = $object->$getter(false);
				if ($value !== null) {
					$a = $this->serializeValue($value, $fragment);
					if ($a) $output[$name] = $a;
				}
			}
		}

		// Serialize the tree objects.
		if ($fragment != "tree" && in_array("tree", $object->getFragmentNames())) {
			$properties = $object->getFragment("tree");
			foreach ($properties as $property) {
				$name = $property["name"];
				$getter = "get".ucwords($name);
				$value = $object->$getter(false);
				if ($value !== null) {
					if ($value instanceof RepositoryObjectArray) {
						$a = $this->serializeValue($value, $fragment);
					} else {
						$a = $this->serialize($value, $fragment);
					}
					if ($a) $output[$name] = $a;
				}
			}
		}

		return $output;
	}

	private function serializeValue($value, $fragment)
	{
		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// Arrays are not to bad either.
		if ($value instanceof RepositoryObjectArray) {
			$output = array();
			foreach ($value->getElements() as $index => $v) {
				$output[$index] = $this->serialize($v, $fragment);
				if ($fragment == "tree")
					$output[$index]["class"] = $v->getClass();
			}
			return $output;
		}

		// RepositoryObjects require a more elaborate procedure.
		if ($value instanceof RepositoryNodeObject) {
			// If the value is inside the tree fragment, only serialize the given fragment.
			// Otherwise serialize all fragments at once.
			if ($value->isInTree()) {
				$output = $this->serialize($value, $fragment);
			} else {
				$output = array();
				foreach ($value->getFragmentNames() as $name) {
					$output = array_merge($output, $this->serialize($value, $name));
				}
			}
			$output["class"] = $value->getClass();
			return $output;
		}

		// References.
		if ($value instanceof RepositoryObjectReference) {
			$id = $value->getId();
			return "@ref ".($id !== null ? $id : "<null>");
		}

		// Complain about the input value now since we're unable to process it.
		throw new \InvalidArgumentException("Unable to serialize value ".get_class($value).".");
	}

	/**
	 * Treats the given input object as the serialized version of the fragment
	 * $fragment of the given object $object and unserializes its contents into
	 * $object.
	 */
	public function unserialize(RepositoryObject $object, $fragment, $input)
	{
		if (!is_array($input) && !is_object($input)) {
			throw new \InvalidArgumentException("Input must either be an array or an object.");
		}
		$this->println(0, "Unserializing $fragment", $object->getId());

		// Unserialize each property individually.
		if (in_array($fragment, $object->getFragmentNames())) {
			$object->{$fragment."_loaded"} = true;
			$properties = $object->getFragment($fragment);
			foreach ($properties as $property) {
				$name = $property["name"];
				$setter = "set".ucwords($name);
				if (isset($input->$name)) {
					$value = $this->unserializeValue($input->$name, $fragment);
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
					$this->println(2, "Also loading $fragment for $name");
					$obj = $object->$getter();
					if (!$obj) {
						throw new \RuntimeException("Object ID {$object->getId()} is expected to have at least a bare version of $name which is not the case. Maybe the tree fragment was not properly loaded?");
					}
					if ($obj instanceof RepositoryObjectArray) {
						$this->unserializeArray($obj, $fragment, $input->$name);
					} else {
						$this->unserialize($obj, $fragment, $input->$name);
					}
				}
			}
		}
	}

	/**
	 * Unserializes the given value and returns the resulting object or value.
	 * This function will produce bare RepositoryObject instances where
	 * appropriate.
	 */
	private function unserializeValue($value, $fragment)
	{
		// References.
		if (is_string($value) && preg_match("/^@ref (.*)/", $value, $m)) {
			$obj = new RepositoryObjectReference($this->repository);
			$obj->set($m[1] == "<null>" ? null : $m[1]);
			return $obj;
		}

		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// Some object.
		if (is_object($value)) {
			if (!isset($value->class)) {
				throw new \InvalidArgumentException("Object value is missing 'class' field required for unserialization: ".print_r($value, true));
			}
			$class = "\\Objects\\".$value->class;
			$this->println(1,"Instantiating bare object $class");
			$obj = new $class(false);

			// Unserialize the object's tree if we're currently unserializing the tree fragment.
			// Otherwise unserialize all fragments of the object as it is contained entirely here.
			if ($fragment == "tree") {
				$this->unserialize($obj, "tree", $value);
			} else {
				foreach ($obj->getFragmentNames() as $name) {
					$this->unserialize($obj, $name, $value);
				}
			}

			return $obj;
		}

		// Some array.
		if (is_array($value)) {
			$array = new RepositoryObjectArray;
			foreach ($value as $i => $v) {
				$array->set($i, $this->unserializeValue($v, $fragment));
			}
			return $array;
		}

		// Complain about the input as we obviously can't process it.
		throw new \InvalidArgumentException("Unable to unserialize value: ".print_r($value, true));
	}

	/**
	 * Performs the same task on arrays as unserialize() performs on objects.
	 */
	private function unserializeArray(RepositoryObjectArray $array, $fragment, array $input)
	{
		foreach ($input as $index => $value) {
			$this->unserialize($array->get($index), $fragment, $value);
		}
	}

	// Logging facilities.
	static public $verbosity = 0;
	private function println($verbosity, $ln, $info = null)
	{
		if (static::$verbosity > $verbosity)
			Log::println($ln, get_class(), $info);
	}
}