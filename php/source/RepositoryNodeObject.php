<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class RepositoryNodeObject extends RepositoryObject implements RepositoryObjectParentInterface
{
	/**
	 * Returns the object's ID which consists of the root ID and the tree path
	 * to the object.
	 */
	public function getId()
	{
		if ($this->parent) {
			return $this->parent->getId().".".$this->parent_key;
		} else {
			return "<parentless>";
		}
	}

	/**
	 * Returns true if this object is part of its parent's tree fragment.
	 */
	public function isInTree()
	{
		if ($this->parent_fragment != "tree")
			return false;
		if ($this->parent instanceof RepositoryRootObject)
			return true;
		return $this->parent->isInTree();
	}

	/**
	 * Called by subclasses to lazily load the requested fragment from the
	 * repository. Node objects send the request up the object tree until a
	 * root object finally delegates the load off to the repository.
	 */
	protected function loadFragment($fragment)
	{
		// If this object contains this fragment make sure it is not already loaded.
		if (in_array($fragment, $this->getFragmentNames())) {
			if ($this->{$fragment."_loaded"}) {
				throw new \InvalidArgumentException("Asked to load fragment $fragment which is already loaded.");
			}
		}

		// Ask our parent to load the fragment.
		if (!$this->parent) {
			throw new \RuntimeException("Unable to load fragment $fragment since the object does not have a parent.");
		}
		$this->parent->loadFragment($fragment);
	}

	public function notifyFragmentDirty($fragment)
	{
		// If this object contains this fragment mark it as dirty.
		if (in_array($fragment, $this->getFragmentNames())) {
			// If the fragment is already marked simply return.
			if ($this->{$fragment."_dirty"})
				return;

			// Otherwise mark it as dirty.
			$this->{$fragment."_dirty"} = true;
		}

		// Ask our parent to load the fragment.
		if (!$this->parent) {
			return;
			throw new \RuntimeException("Unable to mark fragment $fragment dirty since the object does not have a parent.");
		}
		$frag = ($this->parent_fragment == "tree" ? $fragment : $this->parent_fragment);
		/*if ($frag != $fragment) {
			$this->println("Fragment $fragment translated to parent's $frag");
		}*/
		$this->parent->notifyFragmentDirty($frag);
	}

	protected function notifyObjectDirty($id)
	{
		if ($this->parent) {
			$cid = $this->parent_key;
			if ($id !== null) {
				$cid = $cid.".".$id;
			}
			$this->parent->notifyObjectDirty($cid);
		}
	}
}