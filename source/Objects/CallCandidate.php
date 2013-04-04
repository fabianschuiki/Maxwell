<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallCandidate extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// call fragment
	public $call_dirty  = false;
	public $call_loaded = true;
	protected $func;
	protected $feasible;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("call");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "call": return array(
				array("name" => "func", "type" => "\RepositoryObjectReference"), 
				array("name" => "feasible", "type" => "bool"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallCandidate";
	}
	
	
	/* ACCESSORS */
	public function setFunc(\RepositoryObjectReference $func = null, $notify = true)
	{
		if ($this->func !== $func) {
			if (!$this->call_loaded) {
				$this->loadFragment('call');
			}
			if ($this->func instanceof \RepositoryObjectParentInterface) $this->func->setParent(null);
			$this->func = $func;
			if ($func instanceof \RepositoryObjectParentInterface) $func->setParent($this, "func", "call");
			if ($notify) {
				$this->notifyFragmentDirty('call');
			}
		}
	}
	public function getFunc($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->func === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null func.");
		}
		return $this->func;
	}
	
	public function setFeasible($feasible, $notify = true)
	{
		if (!is_bool($feasible)) {
			throw new \InvalidArgumentException("feasible needs to be a boolean");
		}
		if ($this->feasible !== $feasible) {
			if (!$this->call_loaded) {
				$this->loadFragment('call');
			}
			$this->feasible = $feasible;
			if ($notify) {
				$this->notifyFragmentDirty('call');
			}
		}
	}
	public function getFeasible($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->feasible === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null feasible.");
		}
		return $this->feasible;
	}
}