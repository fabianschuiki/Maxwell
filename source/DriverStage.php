<?php
/* Copyright © 2013 Fabian Schuiki */

class DriverStage
{
	protected $repository;
	protected $currentObject = null;

	public function __construct(\Repository $repo)
	{
		$this->repository = $repo;
	}

	public function run($objectId)
	{
		$object = $this->repository->getObject($objectId);
		$this->currentObject = $object;
		$this->process($object);
		$this->currentObject = null;
	}

	protected function println($verbosity, $ln, $info = null)
	{
		if (static::$verbosity > $verbosity)
			Log::println($ln, get_class($this), ($this->currentObject ? $this->currentObject->getId() : null));
	}
}
