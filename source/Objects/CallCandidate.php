<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallCandidate extends \RepositoryNodeObject implements \EqualInterface, TypeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $arguments;
	
	// call fragment
	public $call_dirty  = false;
	public $call_loaded = true;
	protected $func;
	protected $feasible;
	protected $cost;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $possibleType;
	protected $requiredType;
	protected $actualType;
	
	
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
		return array("tree","call","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "arguments", "type" => "\RepositoryObjectArray"));
			case "call": return array(
				array("name" => "func", "type" => "\AbstractFunction"), 
				array("name" => "feasible", "type" => "bool"), 
				array("name" => "cost", "type" => "numeric"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallCandidate";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of CallCandidate as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->arguments, $x->arguments)) {
			$this->println(0, "Change detected in arguments");
			return false;
		}
	
		// call fragment
		if (!$this->call_loaded) {
			$this->loadFragment("call");
		}
		if (!$this->areEqual($this->func, $x->func)) {
			$this->println(0, "Change detected in func");
			return false;
		}
		if ($this->feasible !== $x->feasible) {
			$this->println(0, "Change detected in feasible");
			return false;
		}
		if ($this->cost !== $x->cost) {
			$this->println(0, "Change detected in cost");
			return false;
		}
	
		// type fragment
		if (!$this->type_loaded) {
			$this->loadFragment("type");
		}
		if (!$this->areEqual($this->possibleType, $x->possibleType)) {
			$this->println(0, "Change detected in possibleType");
			return false;
		}
		if (!$this->areEqual($this->requiredType, $x->requiredType)) {
			$this->println(0, "Change detected in requiredType");
			return false;
		}
		if (!$this->areEqual($this->actualType, $x->actualType)) {
			$this->println(0, "Change detected in actualType");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setArguments($arguments, $notify = true)
	{
		if (!$arguments instanceof \RepositoryObjectArray && !$arguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs arguments to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->arguments, $arguments)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->arguments instanceof \RepositoryObjectParentInterface) {
				$this->arguments->setParent(null);
			}
			if ($arguments instanceof \RepositoryObjectParentInterface) {
				$arguments->setParent($this, "arguments", "tree");
			}
			$this->arguments = $arguments;
			if ($notify) {
				$this->notifyObjectDirty("arguments");
				$this->notifyFragmentDirty("tree");
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
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->arguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null arguments.");
		}
		if ($unref && $this->arguments instanceof \RepositoryObjectReference) {
			$v = $this->arguments->get();
		} else {
			$v = $this->arguments;
		}
		return $v;
	}
	
	public function setFunc($func, $notify = true)
	{
		if (!$func instanceof \AbstractFunction && !$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \AbstractFunction or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->func, $func)) {
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
			$v = $this->func->get();
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
	
	public function setCost($cost, $notify = true)
	{
		if (!is_numeric($cost)) {
			throw new \InvalidArgumentException("cost needs to be a number");
		}
		if ($this->cost !== $cost) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			$this->cost = $cost;
			if ($notify) {
				$this->notifyObjectDirty("cost");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function getCost($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->cost === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null cost.");
		}
		return $this->cost;
	}
	
	public function setPossibleType($possibleType, $notify = true)
	{
		if (!$this->areEqual($this->possibleType, $possibleType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->possibleType instanceof \RepositoryObjectParentInterface) {
				$this->possibleType->setParent(null);
			}
			if ($possibleType instanceof \RepositoryObjectParentInterface) {
				$possibleType->setParent($this, "possibleType", "type");
			}
			$this->possibleType = $possibleType;
			if ($notify) {
				$this->notifyObjectDirty("possibleType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setPossibleTypeRef($possibleType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($possibleType instanceof \RepositoryObjectReference) {
			$v->set($possibleType->getRefId());
		} else {
			$v->set($possibleType);
		}
		$this->setPossibleType($v, $notify);
	}
	public function getPossibleType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->possibleType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null possibleType.");
		}
		if ($unref && $this->possibleType instanceof \RepositoryObjectReference) {
			$v = $this->possibleType->get();
		} else {
			$v = $this->possibleType;
		}
		return $v;
	}
	
	public function setRequiredType($requiredType, $notify = true)
	{
		if (!$this->areEqual($this->requiredType, $requiredType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->requiredType instanceof \RepositoryObjectParentInterface) {
				$this->requiredType->setParent(null);
			}
			if ($requiredType instanceof \RepositoryObjectParentInterface) {
				$requiredType->setParent($this, "requiredType", "type");
			}
			$this->requiredType = $requiredType;
			if ($notify) {
				$this->notifyObjectDirty("requiredType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setRequiredTypeRef($requiredType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($requiredType instanceof \RepositoryObjectReference) {
			$v->set($requiredType->getRefId());
		} else {
			$v->set($requiredType);
		}
		$this->setRequiredType($v, $notify);
	}
	public function getRequiredType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->requiredType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null requiredType.");
		}
		if ($unref && $this->requiredType instanceof \RepositoryObjectReference) {
			$v = $this->requiredType->get();
		} else {
			$v = $this->requiredType;
		}
		return $v;
	}
	
	public function setActualType($actualType, $notify = true)
	{
		if (!$this->areEqual($this->actualType, $actualType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->actualType instanceof \RepositoryObjectParentInterface) {
				$this->actualType->setParent(null);
			}
			if ($actualType instanceof \RepositoryObjectParentInterface) {
				$actualType->setParent($this, "actualType", "type");
			}
			$this->actualType = $actualType;
			if ($notify) {
				$this->notifyObjectDirty("actualType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setActualTypeRef($actualType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($actualType instanceof \RepositoryObjectReference) {
			$v->set($actualType->getRefId());
		} else {
			$v->set($actualType);
		}
		$this->setActualType($v, $notify);
	}
	public function getActualType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->actualType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null actualType.");
		}
		if ($unref && $this->actualType instanceof \RepositoryObjectReference) {
			$v = $this->actualType->get();
		} else {
			$v = $this->actualType;
		}
		return $v;
	}
}