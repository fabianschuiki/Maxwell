<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class TypeSet extends \RepositoryNodeObject
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
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
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
		return "TypeSet";
	}
	
	
	/* ACCESSORS */
	public function setTypes(\RepositoryObjectArray $types = null, $notify = true)
	{
		if ($this->types !== $types) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->types instanceof \RepositoryObjectParentInterface) $this->types->setParent(null);
			$this->types = $types;
			if ($types instanceof \RepositoryObjectParentInterface) $types->setParent($this, "types", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getTypes($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->types === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null types.");
		}
		return $this->types;
	}
}