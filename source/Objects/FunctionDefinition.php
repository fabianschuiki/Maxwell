<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionDefinition extends \RepositoryRootObject implements RangeInterface, TypeInterface
{
	/* PROPERTIES */
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $range;
	protected $humanRange;
	protected $name;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = false;
	protected $type;
	
	
	/* GENERAL */
	public function getFragmentNames()
	{
		return array("main","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => ""));
			case "type": return array(
				array("name" => "type", "type" => "Type"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	
	/* ACCESSORS */
	public function setRange(\Source\Range $range = null)
	{
		if ($this->range !== $range) {
			$this->range = $range;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getRange()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->range;
	}
	
	public function setHumanRange(\Source\Range $humanRange = null)
	{
		if ($this->humanRange !== $humanRange) {
			$this->humanRange = $humanRange;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getHumanRange()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->humanRange;
	}
	
	public function setName($name)
	{
		if ($this->name !== $name) {
			$this->name = $name;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getName()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->name;
	}
	
	public function setType(Type $type = null)
	{
		if ($this->type !== $type) {
			$this->type = $type;
			$this->type_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'type');
		}
	}
	public function getType()
	{
		if (!$this->type_loaded) {
			$this->repository->loadObjectFragment($this, 'type');
		}
		return $this->type;
	}
}