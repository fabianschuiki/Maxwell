<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class RepositoryObject
{
	abstract public function getId();

	/// Returns the class name of this object.
	abstract public function getClass();

	abstract public function getFragmentNames();
	abstract public function getFragment($fragment);

	abstract protected function loadFragment($fragment);
	abstract protected function notifyFragmentDirty($fragment);

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
}