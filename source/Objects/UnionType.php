<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class UnionType extends \RepositoryNodeObject implements \EqualInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $types;
	
	
	/* GENERAL */
	public function setParent(\IdedObject $parent = null, $key = null, $fragment = null)
	{
		if ($this->parent !== null && $parent !== null) {
			throw new \RuntimeException("Setting parent to {$parent->getId()} when object already has parent {$this->parent->getId()} (".get_class($this->parent).").");
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
				array("name" => "types", "type" => "\RepositoryObjectArray"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "UnionType";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of UnionType as well.');
		}
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->types, $x->types)) {
			$this->println(0, "Change detected in types");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setTypes($types, $notify = true)
	{
		if (!$types instanceof \RepositoryObjectArray && !$types instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs types to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->types, $types)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->types instanceof \RepositoryObjectParentInterface) {
				$this->types->setParent(null);
			}
			if ($types instanceof \RepositoryObjectParentInterface) {
				$types->setParent($this, "types", "main");
			}
			$this->types = $types;
			if ($notify) {
				$this->notifyObjectDirty("types");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setTypesRef($types, \Repository $repository, $notify = true)
	{
		if (!$types instanceof \RepositoryObjectArray && !$types instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs types to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($types instanceof \RepositoryObjectReference) {
			$v->set($types->getRefId());
		} else {
			$v->set($types);
		}
		$this->setTypes($v, $notify);
	}
	public function getTypes($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->types === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null types.");
		}
		if ($unref && $this->types instanceof \RepositoryObjectReference) {
			$v = $this->types->get();
		} else {
			$v = $this->types;
		}
		return $v;
	}
}