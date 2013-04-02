<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class DriverStage
{
	protected $repository;
	protected $currentObject = null;

	public function __construct(\Repository $repo)
	{
		$this->repository = $repo;
	}

	/**
	 * Runs this stage on the object with ID $objectId. Calls process() on the
	 * object retrieved from the repository. Subclasses may want to override
	 * process().
	 */
	public function run($objectId)
	{
		$this->println(0, "Running on $objectId");
		$object = $this->repository->getObject($objectId);
		$this->currentObject = $object;
		$this->process($object);
		$this->currentObject = null;
	}

	/// Process the given object.
	abstract protected function process(RepositoryObject $object);

	/**
	 * Prints the given line to the console if the configured verbosity is
	 * greater than $verbosity. If this function is called inside process()
	 * the object ID that was passed to run() is displayed as metadata.
	 */
	protected function println($verbosity, $ln, $info = null)
	{
		if (static::$verbosity > $verbosity) {
			if ($info === null) {
				$info = ($this->currentObject ? $this->currentObject->getId() : null);
			}
			Log::println($ln, get_class($this), $info);
		}
	}
}
