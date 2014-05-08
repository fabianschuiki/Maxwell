<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionType extends \RepositoryNodeObject implements \EqualInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $inputs;
	protected $outputs;
	
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
				array("name" => "inputs", "type" => "FunctionArgumentTupleType"), 
				array("name" => "outputs", "type" => "FunctionArgumentTupleType"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionType";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of FunctionType as well.');
		}
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->inputs, $x->inputs)) {
			$this->println(0, "Change detected in inputs");
			return false;
		}
		if (!$this->areEqual($this->outputs, $x->outputs)) {
			$this->println(0, "Change detected in outputs");
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
	public function setInputs($inputs, $notify = true)
	{
		if (!$inputs instanceof FunctionArgumentTupleType && !$inputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inputs to be an instance of FunctionArgumentTupleType or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->inputs, $inputs)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->inputs instanceof \RepositoryObjectParentInterface) {
				$this->inputs->setParent(null);
			}
			if ($inputs instanceof \RepositoryObjectParentInterface) {
				$inputs->setParent($this, "inputs", "main");
			}
			$this->inputs = $inputs;
			if ($notify) {
				$this->notifyObjectDirty("inputs");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setInputsRef($inputs, \Repository $repository, $notify = true)
	{
		if (!$inputs instanceof FunctionArgumentTupleType && !$inputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inputs to be an instance of FunctionArgumentTupleType or \RepositoryObjectReference');
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
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->inputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inputs.");
		}
		if ($unref && $this->inputs instanceof \RepositoryObjectReference) {
			$v = $this->inputs->get();
		} else {
			$v = $this->inputs;
		}
		return $v;
	}
	
	public function setOutputs($outputs, $notify = true)
	{
		if (!$outputs instanceof FunctionArgumentTupleType && !$outputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs outputs to be an instance of FunctionArgumentTupleType or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->outputs, $outputs)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->outputs instanceof \RepositoryObjectParentInterface) {
				$this->outputs->setParent(null);
			}
			if ($outputs instanceof \RepositoryObjectParentInterface) {
				$outputs->setParent($this, "outputs", "main");
			}
			$this->outputs = $outputs;
			if ($notify) {
				$this->notifyObjectDirty("outputs");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setOutputsRef($outputs, \Repository $repository, $notify = true)
	{
		if (!$outputs instanceof FunctionArgumentTupleType && !$outputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs outputs to be an instance of FunctionArgumentTupleType or \RepositoryObjectReference');
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
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->outputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null outputs.");
		}
		if ($unref && $this->outputs instanceof \RepositoryObjectReference) {
			$v = $this->outputs->get();
		} else {
			$v = $this->outputs;
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