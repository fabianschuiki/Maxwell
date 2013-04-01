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
		if (!in_array($fragment, $this->getFragmentNames())) {
			throw new \InvalidArgumentException("Asked to load fragment $fragment which does not exist.");
		}
		if ($this->{$fragment."_loaded"}) {
			throw new \InvalidArgumentException("Asked to load fragment $fragment which is already loaded.");
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
		echo "Would notify root object {$this->id}'s fragment $fragment dirty\n";
	}
}