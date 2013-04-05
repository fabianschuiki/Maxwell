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
	protected $arguments;
	
	
	/* GENERAL */
	public function setParent(\IdedObject $parent = null, $key = null, $fragment = null)
	{
		if ($this->parent !== null && $parent !== null) {
			throw new \RuntimeException("Setting parent to {$parent->getId()} when object already has parent {$this->parent->getId()}.");
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
		return array("call");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "call": return array(
				array("name" => "func", "type" => "\AbstractFunction"), 
				array("name" => "feasible", "type" => "bool"), 
				array("name" => "arguments", "type" => "\RepositoryObjectArray"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallCandidate";
	}
	
	
	/* ACCESSORS */
	public function setFunc($func, $notify = true)
	{
		if (!$func instanceof \AbstractFunction && !$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \AbstractFunction or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->func, $func)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->func instanceof \RepositoryObjectParentInterface) {
				$this->func->setParent(null);
			}
			if ($func instanceof \RepositoryObjectParentInterface) {
				$func->setParent($this, "func", "call");
			}
			$this->func = $func;
			if ($notify) {
				$this->notifyObjectDirty("func");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setFuncRef($func, \Repository $repository, $notify = true)
	{
		if (!$func instanceof \AbstractFunction && !$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \AbstractFunction or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($func instanceof \RepositoryObjectReference) {
			$v->set($func->getRefId());
		} else {
			$v->set($func);
		}
		$this->setFunc($v, $notify);
	}
	public function getFunc($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->func === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null func.");
		}
		if ($unref && $this->func instanceof \RepositoryObjectReference) {
			$v = $this->func->get(!$enforce);
		} else {
			$v = $this->func;
		}
		return $v;
	}
	
	public function setFeasible($feasible, $notify = true)
	{
		if (!is_bool($feasible)) {
			throw new \InvalidArgumentException("feasible needs to be a boolean");
		}
		if ($this->feasible !== $feasible) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			$this->feasible = $feasible;
			if ($notify) {
				$this->notifyObjectDirty("feasible");
				$this->notifyFragmentDirty("call");
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
	
	public function setArguments($arguments, $notify = true)
	{
		if (!$arguments instanceof \RepositoryObjectArray && !$arguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs arguments to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->arguments, $arguments)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->arguments instanceof \RepositoryObjectParentInterface) {
				$this->arguments->setParent(null);
			}
			if ($arguments instanceof \RepositoryObjectParentInterface) {
				$arguments->setParent($this, "arguments", "call");
			}
			$this->arguments = $arguments;
			if ($notify) {
				$this->notifyObjectDirty("arguments");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setArgumentsRef($arguments, \Repository $repository, $notify = true)
	{
		if (!$arguments instanceof \RepositoryObjectArray && !$arguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs arguments to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($arguments instanceof \RepositoryObjectReference) {
			$v->set($arguments->getRefId());
		} else {
			$v->set($arguments);
		}
		$this->setArguments($v, $notify);
	}
	public function getArguments($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->arguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null arguments.");
		}
		if ($unref && $this->arguments instanceof \RepositoryObjectReference) {
			$v = $this->arguments->get(!$enforce);
		} else {
			$v = $this->arguments;
		}
		return $v;
	}
}