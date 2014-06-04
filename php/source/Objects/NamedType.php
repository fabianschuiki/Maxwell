<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class NamedType extends \RepositoryNodeObject implements \EqualInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $name;
	
	// binding fragment
	public $binding_dirty  = false;
	public $binding_loaded = true;
	protected $definition;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	
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
		return array("main","binding","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "name", "type" => "string"));
			case "binding": return array(
				array("name" => "definition", "type" => "\RepositoryObjectReference"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
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
	
		// binding fragment
		if (!$this->binding_loaded) {
			$this->loadFragment("binding");
		}
		if (!$this->areEqual($this->definition, $x->definition)) {
			$this->println(0, "Change detected in definition");
			return false;
		}
	
		// graph fragment
		if (!$this->graph_loaded) {
			$this->loadFragment("graph");
		}
		if (!$this->areEqual($this->graphPrev, $x->graphPrev)) {
			$this->println(0, "Change detected in graphPrev");
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
			if (!$this->binding_loaded) {
				$this->loadFragment("binding");
			}
			if ($this->definition instanceof \RepositoryObjectParentInterface) {
				$this->definition->setParent(null);
			}
			if ($definition instanceof \RepositoryObjectParentInterface) {
				$definition->setParent($this, "definition", "binding");
			}
			$this->definition = $definition;
			if ($notify) {
				$this->notifyObjectDirty("definition");
				$this->notifyFragmentDirty("binding");
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
		if (!$this->binding_loaded) {
			$this->loadFragment('binding');
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
	
	public function setGraphPrev($graphPrev, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->graphPrev, $graphPrev)) {
			if (!$this->graph_loaded) {
				$this->loadFragment("graph");
			}
			if ($this->graphPrev instanceof \RepositoryObjectParentInterface) {
				$this->graphPrev->setParent(null);
			}
			if ($graphPrev instanceof \RepositoryObjectParentInterface) {
				$graphPrev->setParent($this, "graphPrev", "graph");
			}
			$this->graphPrev = $graphPrev;
			if ($notify) {
				$this->notifyObjectDirty("graphPrev");
				$this->notifyFragmentDirty("graph");
			}
		}
	}
	public function setGraphPrevRef($graphPrev, \Repository $repository, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($graphPrev instanceof \RepositoryObjectReference) {
			$v->set($graphPrev->getRefId());
		} else {
			$v->set($graphPrev);
		}
		$this->setGraphPrev($v, $notify);
	}
	public function getGraphPrev($enforce = true, $unref = true)
	{
		if (!$this->graph_loaded) {
			$this->loadFragment('graph');
		}
		if ($enforce && $this->graphPrev === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null graphPrev.");
		}
		if ($unref && $this->graphPrev instanceof \RepositoryObjectReference) {
			$v = $this->graphPrev->get();
		} else {
			$v = $this->graphPrev;
		}
		return $v;
	}
}