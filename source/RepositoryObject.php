<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class RepositoryObject implements IdedObject
{
	abstract public function getId();

	/// Returns the class name of this object.
	abstract public function getClass();

	abstract public function getFragmentNames();
	abstract public function getFragment($fragment);

	abstract protected function loadFragment($fragment);
	abstract protected function notifyFragmentDirty($fragment);
	abstract protected function notifyObjectDirty($id);

	public function print_fragmentStates()
	{
		echo $this->getClass()." ".$this->getId()." {\n";
		foreach ($this->getFragmentNames() as $name) {
			echo "   $name: ".($this->{$name."_dirty"} ? "dirty" : ($this->{$name."_loaded"} ? "loaded" : "?"))."\n";
		}
		echo "}\n";
	}

	/**
	 * Writes the given line to the console, prepending it with some metadata
	 * about the object.
	 */
	static public $verbosity = 1;
	protected function println($verbosity, $ln)
	{
		if (static::$verbosity > $verbosity)
			Log::println($ln, $this->getClass(), $this->getId());
	}

	public function __construct($loaded = true)
	{
		if (!$loaded) {
			foreach ($this->getFragmentNames() as $name) {
				$this->{$name."_loaded"} = false;
			}
		}
	}

	/**
	 * Returns the objects in the tree fragment.
	 */
	public function getChildren()
	{
		if (in_array("tree", $this->getFragmentNames())) {
			$props = $this->getFragment("tree");
			foreach ($props as $i => $p) {
				$getter = "get".ucwords($p["name"]);
				$props[$i] = $this->$getter();
			}
			return $props;
		}
		return array();
	}

	public function get($property, $enforce = true)
	{
		$getter = "get".ucfirst($property);
		return $this->$getter($enforce);
	}

	/**
	 * Compares $a and $b and decides whether the property b (i.e. new) has
	 * changed with regards to a (i.e. old). Checks the trivial cases of
	 * identical objects first and if they fail moves to the more sophisticated
	 * isEqualTo() function.
	 */
	public function areEqual($a,$b)
	{
		if ($a === $b)
			return true;
		if ($a === null || $b === null)
			return false;
		if (get_class($a) !== get_class($b))
			return false;
		if ($a instanceof EqualInterface)
			return $a->isEqualTo($b);
		return false;
	}

	/**
	 * Describes the object in a human readable string form. Prints the tree of
	 * objects attached to this.
	 */
	public function describe($header = true)
	{
		$s  = $this->getClass().($header ? " ".$this->getId()." " : " ");
		$s .= "{\n";
		foreach ($this->getFragmentNames() as $fragmentName) {
			//$s .= "  ".strtoupper($fragmentName)."\n";
			foreach ($this->getFragment($fragmentName) as $property) {
				$getter = "get".ucfirst($property["name"]);
				$v = $this->$getter(false, false);
				if ($v === null) continue;
				$s .= " - ".$property["name"].": ";
				if ($v instanceof \RepositoryObjectReference) {
					$id = $v->getRefId();
					$s .= "@ref ".($id !== null ? $id : "<null>");
				} else if ($v instanceof \RepositoryObject) {
					$s .= str_replace("\n", "\n   ", $v->describe(false));
				} else if (is_object($v)) {
					$s .= get_class($v);
				} else {
					$s .= $v;
				}
				$s .= "\n";
			}
		}
		$s .= "}";
		return $s;
	}
}