<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class AssumeStmt extends \RepositoryNodeObject implements \EqualInterface, GraphInterface, AssumerInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $target;
	protected $assumption;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	// assumer fragment
	public $assumer_dirty  = false;
	public $assumer_loaded = true;
	protected $assumptions;
	
	
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
		return array("tree","graph","assumer");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "target", "type" => ""), 
				array("name" => "assumption", "type" => ""));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "assumer": return array(
				array("name" => "assumptions", "type" => "\RepositoryObjectArray"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "AssumeStmt";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of AssumeStmt as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->target, $x->target)) {
			$this->println(0, "Change detected in target");
			return false;
		}
		if (!$this->areEqual($this->assumption, $x->assumption)) {
			$this->println(0, "Change detected in assumption");
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
	
		// assumer fragment
		if (!$this->assumer_loaded) {
			$this->loadFragment("assumer");
		}
		if (!$this->areEqual($this->assumptions, $x->assumptions)) {
			$this->println(0, "Change detected in assumptions");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setTarget($target, $notify = true)
	{
		if (!$this->areEqual($this->target, $target)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->target instanceof \RepositoryObjectParentInterface) {
				$this->target->setParent(null);
			}
			if ($target instanceof \RepositoryObjectParentInterface) {
				$target->setParent($this, "target", "tree");
			}
			$this->target = $target;
			if ($notify) {
				$this->notifyObjectDirty("target");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setTargetRef($target, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($target instanceof \RepositoryObjectReference) {
			$v->set($target->getRefId());
		} else {
			$v->set($target);
		}
		$this->setTarget($v, $notify);
	}
	public function getTarget($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->target === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null target.");
		}
		if ($unref && $this->target instanceof \RepositoryObjectReference) {
			$v = $this->target->get();
		} else {
			$v = $this->target;
		}
		return $v;
	}
	
	public function setAssumption($assumption, $notify = true)
	{
		if (!$this->areEqual($this->assumption, $assumption)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->assumption instanceof \RepositoryObjectParentInterface) {
				$this->assumption->setParent(null);
			}
			if ($assumption instanceof \RepositoryObjectParentInterface) {
				$assumption->setParent($this, "assumption", "tree");
			}
			$this->assumption = $assumption;
			if ($notify) {
				$this->notifyObjectDirty("assumption");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setAssumptionRef($assumption, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($assumption instanceof \RepositoryObjectReference) {
			$v->set($assumption->getRefId());
		} else {
			$v->set($assumption);
		}
		$this->setAssumption($v, $notify);
	}
	public function getAssumption($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->assumption === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null assumption.");
		}
		if ($unref && $this->assumption instanceof \RepositoryObjectReference) {
			$v = $this->assumption->get();
		} else {
			$v = $this->assumption;
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
	
	public function setAssumptions($assumptions, $notify = true)
	{
		if (!$assumptions instanceof \RepositoryObjectArray && !$assumptions instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs assumptions to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->assumptions, $assumptions)) {
			if (!$this->assumer_loaded) {
				$this->loadFragment("assumer");
			}
			if ($this->assumptions instanceof \RepositoryObjectParentInterface) {
				$this->assumptions->setParent(null);
			}
			if ($assumptions instanceof \RepositoryObjectParentInterface) {
				$assumptions->setParent($this, "assumptions", "assumer");
			}
			$this->assumptions = $assumptions;
			if ($notify) {
				$this->notifyObjectDirty("assumptions");
				$this->notifyFragmentDirty("assumer");
			}
		}
	}
	public function setAssumptionsRef($assumptions, \Repository $repository, $notify = true)
	{
		if (!$assumptions instanceof \RepositoryObjectArray && !$assumptions instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs assumptions to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($assumptions instanceof \RepositoryObjectReference) {
			$v->set($assumptions->getRefId());
		} else {
			$v->set($assumptions);
		}
		$this->setAssumptions($v, $notify);
	}
	public function getAssumptions($enforce = true, $unref = true)
	{
		if (!$this->assumer_loaded) {
			$this->loadFragment('assumer');
		}
		if ($enforce && $this->assumptions === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null assumptions.");
		}
		if ($unref && $this->assumptions instanceof \RepositoryObjectReference) {
			$v = $this->assumptions->get();
		} else {
			$v = $this->assumptions;
		}
		return $v;
	}
}