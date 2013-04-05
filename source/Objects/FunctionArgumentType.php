<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionArgumentType extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $name;
	protected $type;
	
	
	/* GENERAL */
	public function setParent(\IdedObject $parent = null, $key = null, $fragment = null)
	{
		if ($this->parent !== null && $parent !== null) {
			throw new \RuntimeException("Setting parent to {$parent->getId()} when object already has parent {$this->parent->getId()}.");
		}
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function __clone()
	{
		$this->parent = null;
		$this->parent_key = null;
		$this->parent_fragment = null;
	}
	
	public function getFragmentNames()
	{
		return array("main");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "name", "type" => "string"), 
				array("name" => "type", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionArgumentType";
	}
	
	
	/* ACCESSORS */
	public function setName($name, $notify = true)
	{
		if (!is_string($name)) {
			throw new \InvalidArgumentException("name needs to be a string");
		}
		if ($this->name !== $name) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			$this->name = $name;
			if ($notify) {
				$this->notifyObjectDirty("name");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function getName($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->name === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null name.");
		}
		return $this->name;
	}
	
	public function setType($type, $notify = true)
	{
		if ($this->hasPropertyChanged($this->type, $type)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->type instanceof \RepositoryObjectParentInterface) {
				$this->type->setParent(null);
			}
			if ($type instanceof \RepositoryObjectParentInterface) {
				$type->setParent($this, "type", "main");
			}
			$this->type = $type;
			if ($notify) {
				$this->notifyObjectDirty("type");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setTypeRef($type, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($type instanceof \RepositoryObjectReference) {
			$v->set($type->getRefId());
		} else {
			$v->set($type);
		}
		$this->setType($v, $notify);
	}
	public function getType($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->type === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null type.");
		}
		if ($unref && $this->type instanceof \RepositoryObjectReference) {
			$v = $this->type->get(!$enforce);
		} else {
			$v = $this->type;
		}
		return $v;
	}
}