<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class ConcreteType extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $definition;
	
	
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
				array("name" => "definition", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "ConcreteType";
	}
	
	
	/* ACCESSORS */
	public function setDefinition(\RepositoryObjectReference $definition = null, $notify = true)
	{
		if ($this->definition !== $definition) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->definition instanceof \RepositoryObjectParentInterface) $this->definition->setParent(null);
			$this->definition = $definition;
			if ($definition instanceof \RepositoryObjectParentInterface) $definition->setParent($this, "definition", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getDefinition($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->definition === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null definition.");
		}
		return $this->definition;
	}
}