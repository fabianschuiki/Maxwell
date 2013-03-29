<?php
/* Copyright © 2013 Fabian Schuiki */

class RepositoryObject
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
}