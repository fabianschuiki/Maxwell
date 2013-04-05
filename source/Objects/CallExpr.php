<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallExpr extends \RepositoryNodeObject implements CallInterface
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
		return array("tree","main","call");
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
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallExpr";
	}
	
	
	/* ACCESSORS */
	public function setArguments($arguments, $notify = true)
	{
		if (!$arguments instanceof \RepositoryObjectArray && !$arguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs arguments to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->arguments, $arguments)) {
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
			$v = $this->arguments->get(!$enforce);
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
		if ($this->hasPropertyChanged($this->callArguments, $callArguments)) {
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
			$v = $this->callArguments->get(!$enforce);
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
		if ($this->hasPropertyChanged($this->callCandidates, $callCandidates)) {
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
			$v = $this->callCandidates->get(!$enforce);
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
		if ($this->hasPropertyChanged($this->selectedCallCandidate, $selectedCallCandidate)) {
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
			$v = $this->selectedCallCandidate->get(!$enforce);
		} else {
			$v = $this->selectedCallCandidate;
		}
		return $v;
	}
}