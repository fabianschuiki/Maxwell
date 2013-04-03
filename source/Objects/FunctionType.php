<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionType extends \RepositoryNodeObject
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
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("main");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "inputs", "type" => "FunctionArgumentTupleType"), 
				array("name" => "outputs", "type" => "FunctionArgumentTupleType"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionType";
	}
	
	
	/* ACCESSORS */
	public function setInputs(FunctionArgumentTupleType $inputs = null, $notify = true)
	{
		if ($this->inputs !== $inputs) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->inputs instanceof \RepositoryObjectParentInterface) $this->inputs->setParent(null);
			$this->inputs = $inputs;
			if ($inputs instanceof \RepositoryObjectParentInterface) $inputs->setParent($this, "inputs", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getInputs($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->inputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inputs.");
		}
		return $this->inputs;
	}
	
	public function setOutputs(FunctionArgumentTupleType $outputs = null, $notify = true)
	{
		if ($this->outputs !== $outputs) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->outputs instanceof \RepositoryObjectParentInterface) $this->outputs->setParent(null);
			$this->outputs = $outputs;
			if ($outputs instanceof \RepositoryObjectParentInterface) $outputs->setParent($this, "outputs", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getOutputs($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->outputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null outputs.");
		}
		return $this->outputs;
	}
}