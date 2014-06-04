<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class TypeSet extends \RepositoryNodeObject implements \EqualInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $types;
	
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
		return array("main","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "types", "type" => "\RepositoryObjectArray"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "TypeSet";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of TypeSet as well.');
		}
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->types, $x->types)) {
			$this->println(0, "Change detected in types");
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