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
	protected function println($ln)
	{
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

	public function hasPropertyChanged($a,$b)
	{
		if ($a === $b)
			return false;
		if ($a === null || $b === null)
			return true;
		if (get_class($a) !== get_class($b))
			return true;
		if ($a instanceof EqualInterface)
			return !$a->isEqualTo($b);
		return true;
	}
}