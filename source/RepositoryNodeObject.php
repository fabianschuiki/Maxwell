<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class RepositoryNodeObject extends RepositoryObject
{
	/**
	 * Returns the object's ID which consists of the root ID and the tree path
	 * to the object.
	 */
	public function getId()
	{
		if (!$this->parent) {
			throw new \RuntimeException("Asked for ID of object which has no parent.");
		}
		return $this->parent->getId().".".$this->parent_key;
	}

	/**
	 * Called by subclasses to lazily load the requested fragment from the
	 * repository. Node objects send the request up the object tree until a
	 * root object finally delegates the load off to the repository.
	 */
	protected function loadFragment($fragment)
	{
		// Check that the fragment exists and has not been loaded. This helps catching early bugs.
		if (!in_array($fragment, $this->getFragmentNames())) {
			throw new \InvalidArgumentException("Asked to load fragment $fragment which does not exist.");
		}
		if ($this->{$fragment."_loaded"}) {
			throw new \InvalidArgumentException("Asked to load fragment $fragment which is already loaded.");
		}
		$this->{$fragment."_loaded"} = true;

		// Ask our parent to load the fragment.
		if (!$this->parent) {
			throw new \RuntimeException("Unable to load fragment $fragment of object ID {$this->id} since the object does not have a parent.");
		}
		$this->parent->loadFragment($fragment);
	}

	protected function notifyFragmentDirty($fragment)
	{
		echo "Would notify object {$this->id}'s fragment $fragment dirty\n";
	}
}