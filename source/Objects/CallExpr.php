<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallExpr extends \RepositoryNodeObject implements \EqualInterface, CallInterface, TypeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $arguments;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $name;
	
	// call fragment
	public $call_dirty  = false;
	public $call_loaded = true;
	protected $callName;
	protected $callArguments;
	protected $callCandidates;
	protected $selectedCallCandidate;
	
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
		return array("tree","main","call","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "arguments", "type" => "\RepositoryObjectArray"));
			case "main": return array(
				array("name" => "name", "type" => "string"));
			case "call": return array(
				array("name" => "callName", "type" => "string"), 
				array("name" => "callArguments", "type" => "CallArgumentTuple"), 
				array("name" => "callCandidates", "type" => "\RepositoryObjectArray"), 
				array("name" => "selectedCallCandidate", "type" => "CallCandidate"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallExpr";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of CallExpr as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->arguments, $x->arguments)) {
			$this->println(0, "Change detected in arguments");
			return false;
		}
	
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if ($this->name !== $x->name) {
			$this->println(0, "Change detected in name");
			return false;
		}
	
		// call fragment
		if (!$this->call_loaded) {
			$this->loadFragment("call");
		}
		if ($this->callName !== $x->callName) {
			$this->println(0, "Change detected in callName");
			return false;
		}
		if (!$this->areEqual($this->callArguments, $x->callArguments)) {
			$this->println(0, "Change detected in callArguments");
			return false;
		}
		if (!$this->areEqual($this->callCandidates, $x->callCandidates)) {
			$this->println(0, "Change detected in callCandidates");
			return false;
		}
		if (!$this->areEqual($this->selectedCallCandidate, $x->selectedCallCandidate)) {
			$this->println(0, "Change detected in selectedCallCandidate");
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
	
	public function setCallName($callName, $notify = true)
	{
		if (!is_string($callName)) {
			throw new \InvalidArgumentException("callName needs to be a string");
		}
		if ($this->callName !== $callName) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			$this->callName = $callName;
			if ($notify) {
				$this->notifyObjectDirty("callName");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function getCallName($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->callName === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null callName.");
		}
		return $this->callName;
	}
	
	public function setCallArguments($callArguments, $notify = true)
	{
		if (!$callArguments instanceof CallArgumentTuple && !$callArguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs callArguments to be an instance of CallArgumentTuple or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->callArguments, $callArguments)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->callArguments instanceof \RepositoryObjectParentInterface) {
				$this->callArguments->setParent(null);
			}
			if ($callArguments instanceof \RepositoryObjectParentInterface) {
				$callArguments->setParent($this, "callArguments", "call");
			}
			$this->callArguments = $callArguments;
			if ($notify) {
				$this->notifyObjectDirty("callArguments");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setCallArgumentsRef($callArguments, \Repository $repository, $notify = true)
	{
		if (!$callArguments instanceof CallArgumentTuple && !$callArguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs callArguments to be an instance of CallArgumentTuple or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($callArguments instanceof \RepositoryObjectReference) {
			$v->set($callArguments->getRefId());
		} else {
			$v->set($callArguments);
		}
		$this->setCallArguments($v, $notify);
	}
	public function getCallArguments($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->callArguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null callArguments.");
		}
		if ($unref && $this->callArguments instanceof \RepositoryObjectReference) {
			$v = $this->callArguments->get();
		} else {
			$v = $this->callArguments;
		}
		return $v;
	}
	
	public function setCallCandidates($callCandidates, $notify = true)
	{
		if (!$callCandidates instanceof \RepositoryObjectArray && !$callCandidates instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs callCandidates to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->callCandidates, $callCandidates)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->callCandidates instanceof \RepositoryObjectParentInterface) {
				$this->callCandidates->setParent(null);
			}
			if ($callCandidates instanceof \RepositoryObjectParentInterface) {
				$callCandidates->setParent($this, "callCandidates", "call");
			}
			$this->callCandidates = $callCandidates;
			if ($notify) {
				$this->notifyObjectDirty("callCandidates");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setCallCandidatesRef($callCandidates, \Repository $repository, $notify = true)
	{
		if (!$callCandidates instanceof \RepositoryObjectArray && !$callCandidates instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs callCandidates to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($callCandidates instanceof \RepositoryObjectReference) {
			$v->set($callCandidates->getRefId());
		} else {
			$v->set($callCandidates);
		}
		$this->setCallCandidates($v, $notify);
	}
	public function getCallCandidates($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->callCandidates === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null callCandidates.");
		}
		if ($unref && $this->callCandidates instanceof \RepositoryObjectReference) {
			$v = $this->callCandidates->get();
		} else {
			$v = $this->callCandidates;
		}
		return $v;
	}
	
	public function setSelectedCallCandidate($selectedCallCandidate, $notify = true)
	{
		if (!$selectedCallCandidate instanceof CallCandidate && !$selectedCallCandidate instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs selectedCallCandidate to be an instance of CallCandidate or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->selectedCallCandidate, $selectedCallCandidate)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->selectedCallCandidate instanceof \RepositoryObjectParentInterface) {
				$this->selectedCallCandidate->setParent(null);
			}
			if ($selectedCallCandidate instanceof \RepositoryObjectParentInterface) {
				$selectedCallCandidate->setParent($this, "selectedCallCandidate", "call");
			}
			$this->selectedCallCandidate = $selectedCallCandidate;
			if ($notify) {
				$this->notifyObjectDirty("selectedCallCandidate");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setSelectedCallCandidateRef($selectedCallCandidate, \Repository $repository, $notify = true)
	{
		if (!$selectedCallCandidate instanceof CallCandidate && !$selectedCallCandidate instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs selectedCallCandidate to be an instance of CallCandidate or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($selectedCallCandidate instanceof \RepositoryObjectReference) {
			$v->set($selectedCallCandidate->getRefId());
		} else {
			$v->set($selectedCallCandidate);
		}
		$this->setSelectedCallCandidate($v, $notify);
	}
	public function getSelectedCallCandidate($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->selectedCallCandidate === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null selectedCallCandidate.");
		}
		if ($unref && $this->selectedCallCandidate instanceof \RepositoryObjectReference) {
			$v = $this->selectedCallCandidate->get();
		} else {
			$v = $this->selectedCallCandidate;
		}
		return $v;
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