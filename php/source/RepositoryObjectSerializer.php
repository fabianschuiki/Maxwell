<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObjectSerializer
{
	protected $repository;

	public function __construct(Repository $repo)
	{
		$this->repository = $repo;
	}

	public function serialize(RepositoryObject $object, $fragment, $targetFragment = null)
	{
		if ($targetFragment === null)
			$targetFragment = $fragment;
		$this->println(0, "Serializing $fragment into $targetFragment", $object->getId());

		// Array objects are a special case.
		if ($object instanceof RepositoryObjectArray) {
			return $this->serializeValue($object, $fragment, $targetFragment);
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
				$value = $object->$getter(false, false);
				if ($value !== null) {
					$a = $this->serializeValue($value, $fragment, $targetFragment);
					if ($a !== null && !(is_object($a) && count($a) == 0))
					//if ($a)
						$output[$name] = $a;
				}
			}
		}

		// Serialize the tree objects.
		if ($fragment != "tree" && in_array("tree", $object->getFragmentNames())) {
			$properties = $object->getFragment("tree");
			foreach ($properties as $property) {
				$name = $property["name"];
				$getter = "get".ucwords($name);
				$value = $object->$getter(false, false);
				if ($value !== null) {
					if ($value instanceof RepositoryObjectArray || $value instanceof RepositoryObjectReference) {
						$a = $this->serializeValue($value, $fragment, $targetFragment);
					} else {
						$a = $this->serialize($value, $fragment, $targetFragment);
					}
					if ($a !== null && !(is_object($a) && count($a) == 0))
					//if ($a)
						$output[$name] = $a;
				}
			}
		}

		return $output;
	}

	private function serializeValue($value, $fragment, $targetFragment)
	{
		// Strings, numbers and booleans are easy.
		if (is_string($value) || is_numeric($value) || is_bool($value))
			return $value;

		// Arrays are not to bad either.
		if ($value instanceof RepositoryObjectArray) {
			$output = array();
			foreach ($value->getElements() as $index => $v) {
				/*if ($v->isInTree()) {
					$op = $this->serialize($v, $fragment);
				} else {
					$op = array();
					foreach ($v->getFragmentNames() as $name) {
						$op = array_merge($output, $this->serialize($v, $name));
					}
				}
				$output[$index] = $op;*/
				//$output[$index] = $this->serialize($v, $fragment);
				/*if ($fragment == "tree" || !$v->isInTree())
					$output[$index]["class"] = $v->getClass();*/
				$output[$index] = $this->serializeValue($v, $fragment, $targetFragment);
			}
			return $output;
		}

		// RepositoryObjects require a more elaborate procedure.
		if ($value instanceof RepositoryNodeObject) {
			// If the value is inside the tree fragment, only serialize the given fragment.
			// Otherwise serialize all fragments at once.
			if ($value->isInTree()) {
				$output = $this->serialize($value, $fragment, $targetFragment);
			} else {
				$output = array();
				foreach ($value->getFragmentNames() as $name) {
					$output = array_merge($output, $this->serialize($value, $name, $targetFragment));
				}
			}
			if ($targetFragment == "tree" || !$value->isInTree())
				$output["class"] = $value->getClass();
			return $output;
		}

		// References.
		if ($value instanceof RepositoryObjectReference) {
			$id = $value->getRefId();
			return "@ref ".($id !== null ? $id : "<null>");
		}

		// Complain about the input value now since we're unable to process it.
		throw new \InvalidArgumentException("Unable to serialize value ".get_class($value).".".($value instanceof IdedObject ? " Object ID is {$value->getId()}" : ""));
	}

	/**
	 * Treats the given input object as the serialized version of the fragment
	 * $fragment of the given object $object and unserializes its contents into
	 * $object.
	 */
	public function unserialize(RepositoryObject $object, $fragment, $input, $targetFragment = null)
	{
		if (!is_array($input) && !is_object($input)) {
			throw new \InvalidArgumentException("Input must either be an array or an object.");
		}
		if ($targetFragment === null)
			$targetFragment = $fragment;
		$this->println(0, "Unserializing $fragment into $targetFragment", $object->getId());

		// Unserialize each property individually.
		if (in_array($fragment, $object->getFragmentNames())) {
			$object->{$fragment."_loaded"} = true;
			$properties = $object->getFragment($fragment);
			foreach ($properties as $property) {
				$name = $property["name"];
				$setter = "set".ucwords($name);
				if (isset($input->$name)) {
					$value = $this->unserializeValue($input->$name, $fragment, $targetFragment);
					$object->$setter($value, false);
				}
			}
		}

		// Unserialize the tree objects.
		if ($targetFragment != "tree" && in_array("tree", $object->getFragmentNames())) {
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
						$this->unserializeArray($obj, $fragment, $input->$name, $targetFragment);
					} else {
						$this->unserialize($obj, $fragment, $input->$name, $targetFragment);
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
	private function unserializeValue($value, $fragment, $targetFragment)
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
			$obj = new $class($targetFragment != "tree");

			// Unserialize the object's tree if we're currently unserializing the tree fragment.
			// Otherwise unserialize all fragments of the object as it is contained entirely here.
			if ($fragment == "tree" && $targetFragment == "tree") {
				$this->unserialize($obj, "tree", $value);
			} else {
				foreach ($obj->getFragmentNames() as $name) {
					$this->unserialize($obj, $name, $value, $targetFragment);
				}
			}

			return $obj;
		}

		// Some array.
		if (is_array($value)) {
			$array = new RepositoryObjectArray;
			foreach ($value as $i => $v) {
				$array->set($i, $this->unserializeValue($v, $fragment, $targetFragment));
			}
			return $array;
		}

		// Complain about the input as we obviously can't process it.
		throw new \InvalidArgumentException("Unable to unserialize value: ".print_r($value, true));
	}

	/**
	 * Performs the same task on arrays as unserialize() performs on objects.
	 */
	private function unserializeArray(RepositoryObjectArray $array, $fragment, array $input, $targetFragment)
	{
		foreach ($input as $index => $value) {
			$this->unserialize($array->get($index), $fragment, $value, $targetFragment);
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