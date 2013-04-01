<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class RepositoryObject
{
	abstract public function getId();

	/// Returns the class name of this object.
	abstract public function getClass();

	abstract protected function loadFragment($fragment);
	abstract protected function notifyFragmentDirty($fragment);

	public function print_fragmentStates()
	{
		echo $this->getClass()." ".$this->getId()." {\n";
		foreach ($this->getFragmentNames() as $name) {
			echo "\t$name: ".($this->{$name."_dirty"} ? "dirty" : ($this->{$name."_loaded"} ? "loaded" : "?"))."\n";
		}
		echo "}\n";
	}
}