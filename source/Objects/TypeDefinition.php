<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class TypeDefinition extends \RepositoryRootObject implements \EqualInterface, RangeInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $types;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $range;
	protected $humanRange;
	protected $name;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	// binding fragment
	public $binding_dirty  = false;
	public $binding_loaded = true;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	
	
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
		return array("tree","main","graph","binding","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "types", "type" => "\RepositoryObjectArray"));
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "binding": return array();
			case "type": return array();
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "TypeDefinition";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of TypeDefinition as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->types, $x->types)) {
			$this->println(0, "Change detected in types");
			return false;
		}
	
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->range, $x->range)) {
			$this->println(0, "Change detected in range");
			return false;
		}
		if (!$this->areEqual($this->humanRange, $x->humanRange)) {
			$this->println(0, "Change detected in humanRange");
			return false;
		}
		if ($this->name !== $x->name) {
			$this->println(0, "Change detected in name");
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
	
		// binding fragment
		if (!$this->binding_loaded) {
			$this->loadFragment("binding");
		}
	
		// type fragment
		if (!$this->type_loaded) {
			$this->loadFragment("type");
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
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->types instanceof \RepositoryObjectParentInterface) {
				$this->types->setParent(null);
			}
			if ($types instanceof \RepositoryObjectParentInterface) {
				$types->setParent($this, "types", "tree");
			}
			$this->types = $types;
			if ($notify) {
				$this->notifyObjectDirty("types");
				$this->notifyFragmentDirty("tree");
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
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
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
	
	public function setRange($range, $notify = true)
	{
		if (!$range instanceof \Source\Range && !$range instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs range to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->range, $range)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->range instanceof \RepositoryObjectParentInterface) {
				$this->range->setParent(null);
			}
			if ($range instanceof \RepositoryObjectParentInterface) {
				$range->setParent($this, "range", "main");
			}
			$this->range = $range;
			if ($notify) {
				$this->notifyObjectDirty("range");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setRangeRef($range, \Repository $repository, $notify = true)
	{
		if (!$range instanceof \Source\Range && !$range instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs range to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($range instanceof \RepositoryObjectReference) {
			$v->set($range->getRefId());
		} else {
			$v->set($range);
		}
		$this->setRange($v, $notify);
	}
	public function getRange($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->range === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null range.");
		}
		if ($unref && $this->range instanceof \RepositoryObjectReference) {
			$v = $this->range->get();
		} else {
			$v = $this->range;
		}
		return $v;
	}
	
	public function setHumanRange($humanRange, $notify = true)
	{
		if (!$humanRange instanceof \Source\Range && !$humanRange instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs humanRange to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->humanRange, $humanRange)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->humanRange instanceof \RepositoryObjectParentInterface) {
				$this->humanRange->setParent(null);
			}
			if ($humanRange instanceof \RepositoryObjectParentInterface) {
				$humanRange->setParent($this, "humanRange", "main");
			}
			$this->humanRange = $humanRange;
			if ($notify) {
				$this->notifyObjectDirty("humanRange");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setHumanRangeRef($humanRange, \Repository $repository, $notify = true)
	{
		if (!$humanRange instanceof \Source\Range && !$humanRange instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs humanRange to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($humanRange instanceof \RepositoryObjectReference) {
			$v->set($humanRange->getRefId());
		} else {
			$v->set($humanRange);
		}
		$this->setHumanRange($v, $notify);
	}
	public function getHumanRange($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->humanRange === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null humanRange.");
		}
		if ($unref && $this->humanRange instanceof \RepositoryObjectReference) {
			$v = $this->humanRange->get();
		} else {
			$v = $this->humanRange;
		}
		return $v;
	}
	
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