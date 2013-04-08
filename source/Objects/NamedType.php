<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class NamedType extends \RepositoryNodeObject implements \EqualInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $name;
	protected $definition;
	
	
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
				array("name" => "name", "type" => "string"), 
				array("name" => "definition", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "NamedType";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of NamedType as well.');
		}
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if ($this->name !== $x->name) {
			$this->println(0, "Change detected in name");
			return false;
		}
		if (!$this->areEqual($this->definition, $x->definition)) {
			$this->println(0, "Change detected in definition");
			return false;
		}
	
		return true;
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
	
	public function setDefinition($definition, $notify = true)
	{
		if (!$definition instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs definition to be an instance of \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->definition, $definition)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->definition instanceof \RepositoryObjectParentInterface) {
				$this->definition->setParent(null);
			}
			if ($definition instanceof \RepositoryObjectParentInterface) {
				$definition->setParent($this, "definition", "main");
			}
			$this->definition = $definition;
			if ($notify) {
				$this->notifyObjectDirty("definition");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setDefinitionRef($definition, \Repository $repository, $notify = true)
	{
		if (!$definition instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs definition to be an instance of \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($definition instanceof \RepositoryObjectReference) {
			$v->set($definition->getRefId());
		} else {
			$v->set($definition);
		}
		$this->setDefinition($v, $notify);
	}
	public function getDefinition($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->definition === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null definition.");
		}
		if ($unref && $this->definition instanceof \RepositoryObjectReference) {
			$v = $this->definition->get();
		} else {
			$v = $this->definition;
		}
		return $v;
	}
}