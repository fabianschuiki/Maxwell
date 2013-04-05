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
	protected $inputs;
	protected $outputs;
	
	
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
				array("name" => "func", "type" => "\RepositoryObjectReference"), 
				array("name" => "feasible", "type" => "bool"), 
				array("name" => "inputs", "type" => "CallCandidateArgumentTuple"), 
				array("name" => "outputs", "type" => "CallCandidateArgumentTuple"));
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
		if (!$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \RepositoryObjectReference');
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
		if (!$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \RepositoryObjectReference');
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
	
	public function setInputs($inputs, $notify = true)
	{
		if (!$inputs instanceof CallCandidateArgumentTuple && !$inputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inputs to be an instance of CallCandidateArgumentTuple or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->inputs, $inputs)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->inputs instanceof \RepositoryObjectParentInterface) {
				$this->inputs->setParent(null);
			}
			if ($inputs instanceof \RepositoryObjectParentInterface) {
				$inputs->setParent($this, "inputs", "call");
			}
			$this->inputs = $inputs;
			if ($notify) {
				$this->notifyObjectDirty("inputs");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setInputsRef($inputs, \Repository $repository, $notify = true)
	{
		if (!$inputs instanceof CallCandidateArgumentTuple && !$inputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inputs to be an instance of CallCandidateArgumentTuple or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($inputs instanceof \RepositoryObjectReference) {
			$v->set($inputs->getRefId());
		} else {
			$v->set($inputs);
		}
		$this->setInputs($v, $notify);
	}
	public function getInputs($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->inputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inputs.");
		}
		if ($unref && $this->inputs instanceof \RepositoryObjectReference) {
			$v = $this->inputs->get(!$enforce);
		} else {
			$v = $this->inputs;
		}
		return $v;
	}
	
	public function setOutputs($outputs, $notify = true)
	{
		if (!$outputs instanceof CallCandidateArgumentTuple && !$outputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs outputs to be an instance of CallCandidateArgumentTuple or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->outputs, $outputs)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->outputs instanceof \RepositoryObjectParentInterface) {
				$this->outputs->setParent(null);
			}
			if ($outputs instanceof \RepositoryObjectParentInterface) {
				$outputs->setParent($this, "outputs", "call");
			}
			$this->outputs = $outputs;
			if ($notify) {
				$this->notifyObjectDirty("outputs");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setOutputsRef($outputs, \Repository $repository, $notify = true)
	{
		if (!$outputs instanceof CallCandidateArgumentTuple && !$outputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs outputs to be an instance of CallCandidateArgumentTuple or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($outputs instanceof \RepositoryObjectReference) {
			$v->set($outputs->getRefId());
		} else {
			$v->set($outputs);
		}
		$this->setOutputs($v, $notify);
	}
	public function getOutputs($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->outputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null outputs.");
		}
		if ($unref && $this->outputs instanceof \RepositoryObjectReference) {
			$v = $this->outputs->get(!$enforce);
		} else {
			$v = $this->outputs;
		}
		return $v;
	}
}