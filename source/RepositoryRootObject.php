<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class RepositoryRootObject extends RepositoryObject
{
	/// Repository that manages this object.
	protected $repository;

	/// Unique identification number of this object.
	protected $id;

	/**
	 * Creates a new bare repository object managed by $repo with the ID $id.
	 */
	public function __construct(Repository $repo, $id)
	{
		parent::__construct(false);
		if (!is_string($id) && !is_numeric($id)) {
			throw new InvalidArgumentException("Object ID $id is not valid.");
		}
		$this->repository = $repo;
		$this->id = $id;
	}

	public function getId() { return $this->id; }
	public function getRepository() { return $this->repository; }

	/**
	 * Called by subclasses to lazily load a fragment of the object. Root
	 * objects delegate the fragment loading to the Repository class that
	 * manages them.
	 */
	protected function loadFragment($fragment)
	{
		// If this root object contains the fragment, make sure it is not already loaded.
		if (in_array($fragment, $this->getFragmentNames())) {
			if ($this->{$fragment."_loaded"}) {
				throw new \InvalidArgumentException("Asked to load fragment $fragment which is already loaded.");
			}
		}

		// Ask the repository to load the fragment.
		$this->repository->loadObjectFragment($this->id, $fragment);
	}

	/**
	 * Called by subclasses whenever a property in a fragment changes. Root
	 * objects relay this information to the Repository which marks this object
	 * as dirty with respect to the fragment. This causes it to be written to
	 * disk upon the next repository flush.
	 */
	protected function notifyFragmentDirty($fragment)
	{
		// If this root object contains this fragment mark it as dirty.
		if (in_array($fragment, $this->getFragmentNames()))
		{
			// Make sure the fragment was loaded.
			if (!$this->{$fragment."_loaded"}) {
				throw new \RuntimeException("Cannot mark unloaded fragment $fragment of {$this->id} as dirty.");
			}

			// If the fragment is already marked simply return.
			if ($this->{$fragment."_dirty"})
				return;

			// Otherwise mark it as dirty.
			$this->{$fragment."_dirty"} = true;
		}

		// Notify the repository about the fragment being marked as dirty.
		$this->repository->notifyObjectFragmentDirty($this->id, $fragment);
	}

	protected function notifyObjectDirty($id)
	{
		$this->repository->notifyObjectDirty($this->id, $id);
	}
}