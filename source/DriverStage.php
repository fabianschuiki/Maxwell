<?php
/* Copyright © 2013 Fabian Schuiki */

abstract class DriverStage
{
	protected $repository;
	protected $currentObject = null;
	protected $name = null;

	public function __construct(\Repository $repo)
	{
		$this->repository = $repo;
	}

	/**
	 * Returns the stage's name.
	 */
	public function getName()
	{
		if ($this->name === null) {
			$this->name = preg_replace('/^([^\\\\]*\\\\)+/', "", get_class($this));
		}
		return $this->name;
	}

	/**
	 * Runs this stage on the object with ID $objectId. Calls process() on the
	 * object retrieved from the repository. Subclasses may want to override
	 * process().
	 */
	public function run($objectId)
	{
		$this->println(0, "Running on $objectId");
		$this->repository->resetStageDependencies($this->getName(), $objectId);
		$object = $this->repository->getObject($objectId);
		$this->currentObject = $object;
		$this->process($object);
		$this->currentObject = null;
		$this->repository->setObjectStageState($objectId, $this->getName(), true);
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

	/**
	 * Adds a dependency to the repository linking this stage and the current
	 * object to the given dependency object. Whenever the given $object
	 * changes the stage needs to be re-run.
	 */
	protected function addDependency($object)
	{
		if ($object instanceof Builtin\BuiltinObject) {
			return;
		}
		if (!$object instanceof RepositoryObject) {
			throw new InvalidArgumentException("Dependency object must be a RepositoryObject.");
		}
		$id = (is_object($object) ? ($object instanceof \RepositoryObjectReference ? $object->getRefId() : $object->getId()) : $object);
		if (preg_match('/<parentless>/', $id)) {
			throw new InvalidArgumentException("Dependency object $id is invalid as it is not part of the root object.");
		}
		if (preg_match('/^0\./', $id)) {
			return;
		}

		$canonical = array($id);
		foreach ($canonical as $id) {
			$this->repository->addStageDependency(
				$this->getName(),
				$this->currentObject->getId(),
				$id);
		}
	}
}
