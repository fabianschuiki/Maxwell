<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class StructureType extends \RepositoryNodeObject implements \EqualInterface, RangeInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $fields;
	protected $inherits;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $range;
	protected $humanRange;
	
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
		return array("tree","main","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "fields", "type" => "\RepositoryObjectArray"), 
				array("name" => "inherits", "type" => "\RepositoryObjectArray"));
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "StructureType";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of StructureType as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->fields, $x->fields)) {
			$this->println(0, "Change detected in fields");
			return false;
		}
		if (!$this->areEqual($this->inherits, $x->inherits)) {
			$this->println(0, "Change detected in inherits");
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
	public function setFields($fields, $notify = true)
	{
		if (!$fields instanceof \RepositoryObjectArray && !$fields instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs fields to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->fields, $fields)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->fields instanceof \RepositoryObjectParentInterface) {
				$this->fields->setParent(null);
			}
			if ($fields instanceof \RepositoryObjectParentInterface) {
				$fields->setParent($this, "fields", "tree");
			}
			$this->fields = $fields;
			if ($notify) {
				$this->notifyObjectDirty("fields");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setFieldsRef($fields, \Repository $repository, $notify = true)
	{
		if (!$fields instanceof \RepositoryObjectArray && !$fields instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs fields to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($fields instanceof \RepositoryObjectReference) {
			$v->set($fields->getRefId());
		} else {
			$v->set($fields);
		}
		$this->setFields($v, $notify);
	}
	public function getFields($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->fields === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null fields.");
		}
		if ($unref && $this->fields instanceof \RepositoryObjectReference) {
			$v = $this->fields->get();
		} else {
			$v = $this->fields;
		}
		return $v;
	}
	
	public function setInherits($inherits, $notify = true)
	{
		if (!$inherits instanceof \RepositoryObjectArray && !$inherits instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inherits to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->inherits, $inherits)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->inherits instanceof \RepositoryObjectParentInterface) {
				$this->inherits->setParent(null);
			}
			if ($inherits instanceof \RepositoryObjectParentInterface) {
				$inherits->setParent($this, "inherits", "tree");
			}
			$this->inherits = $inherits;
			if ($notify) {
				$this->notifyObjectDirty("inherits");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setInheritsRef($inherits, \Repository $repository, $notify = true)
	{
		if (!$inherits instanceof \RepositoryObjectArray && !$inherits instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inherits to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($inherits instanceof \RepositoryObjectReference) {
			$v->set($inherits->getRefId());
		} else {
			$v->set($inherits);
		}
		$this->setInherits($v, $notify);
	}
	public function getInherits($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->inherits === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inherits.");
		}
		if ($unref && $this->inherits instanceof \RepositoryObjectReference) {
			$v = $this->inherits->get();
		} else {
			$v = $this->inherits;
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