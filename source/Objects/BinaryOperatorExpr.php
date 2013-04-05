<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class BinaryOperatorExpr extends Expr implements GraphInterface, CallInterface, TypeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $lhs;
	protected $rhs;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $operator;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
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
		return array("tree","main","graph","call","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "lhs", "type" => "Expr"), 
				array("name" => "rhs", "type" => "Expr"));
			case "main": return array(
				array("name" => "operator", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
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
		return "BinaryOperatorExpr";
	}
	
	
	/* ACCESSORS */
	public function setLhs($lhs, $notify = true)
	{
		if (!$lhs instanceof Expr && !$lhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs lhs to be an instance of Expr or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->lhs, $lhs)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->lhs instanceof \RepositoryObjectParentInterface) {
				$this->lhs->setParent(null);
			}
			if ($lhs instanceof \RepositoryObjectParentInterface) {
				$lhs->setParent($this, "lhs", "tree");
			}
			$this->lhs = $lhs;
			if ($notify) {
				$this->notifyObjectDirty("lhs");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setLhsRef($lhs, \Repository $repository, $notify = true)
	{
		if (!$lhs instanceof Expr && !$lhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs lhs to be an instance of Expr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($lhs instanceof \RepositoryObjectReference) {
			$v->set($lhs->getRefId());
		} else {
			$v->set($lhs);
		}
		$this->setLhs($v, $notify);
	}
	public function getLhs($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->lhs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null lhs.");
		}
		if ($unref && $this->lhs instanceof \RepositoryObjectReference) {
			$v = $this->lhs->get(!$enforce);
		} else {
			$v = $this->lhs;
		}
		return $v;
	}
	
	public function setRhs($rhs, $notify = true)
	{
		if (!$rhs instanceof Expr && !$rhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs rhs to be an instance of Expr or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->rhs, $rhs)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->rhs instanceof \RepositoryObjectParentInterface) {
				$this->rhs->setParent(null);
			}
			if ($rhs instanceof \RepositoryObjectParentInterface) {
				$rhs->setParent($this, "rhs", "tree");
			}
			$this->rhs = $rhs;
			if ($notify) {
				$this->notifyObjectDirty("rhs");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setRhsRef($rhs, \Repository $repository, $notify = true)
	{
		if (!$rhs instanceof Expr && !$rhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs rhs to be an instance of Expr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($rhs instanceof \RepositoryObjectReference) {
			$v->set($rhs->getRefId());
		} else {
			$v->set($rhs);
		}
		$this->setRhs($v, $notify);
	}
	public function getRhs($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->rhs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null rhs.");
		}
		if ($unref && $this->rhs instanceof \RepositoryObjectReference) {
			$v = $this->rhs->get(!$enforce);
		} else {
			$v = $this->rhs;
		}
		return $v;
	}
	
	public function setOperator($operator, $notify = true)
	{
		if (!is_string($operator)) {
			throw new \InvalidArgumentException("operator needs to be a string");
		}
		if ($this->operator !== $operator) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			$this->operator = $operator;
			if ($notify) {
				$this->notifyObjectDirty("operator");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function getOperator($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->operator === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null operator.");
		}
		return $this->operator;
	}
	
	public function setGraphPrev($graphPrev, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->graphPrev, $graphPrev)) {
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
			$v = $this->graphPrev->get(!$enforce);
		} else {
			$v = $this->graphPrev;
		}
		return $v;
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
	
	public function setPossibleType($possibleType, $notify = true)
	{
		if ($this->hasPropertyChanged($this->possibleType, $possibleType)) {
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
			$v = $this->possibleType->get(!$enforce);
		} else {
			$v = $this->possibleType;
		}
		return $v;
	}
	
	public function setRequiredType($requiredType, $notify = true)
	{
		if ($this->hasPropertyChanged($this->requiredType, $requiredType)) {
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
			$v = $this->requiredType->get(!$enforce);
		} else {
			$v = $this->requiredType;
		}
		return $v;
	}
	
	public function setActualType($actualType, $notify = true)
	{
		if ($this->hasPropertyChanged($this->actualType, $actualType)) {
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
			$v = $this->actualType->get(!$enforce);
		} else {
			$v = $this->actualType;
		}
		return $v;
	}
}