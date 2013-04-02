<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class BinaryOperatorExpr extends Expr implements GraphInterface, CallInterface
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
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("tree","main","graph","call");
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
				array("name" => "callArguments", "type" => "CallArgumentTuple"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "BinaryOperatorExpr";
	}
	
	
	/* ACCESSORS */
	public function setLhs(Expr $lhs = null, $notify = true)
	{
		if ($this->lhs !== $lhs) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->lhs instanceof \RepositoryObjectParentInterface) $this->lhs->setParent(null);
			$this->lhs = $lhs;
			if ($lhs instanceof \RepositoryObjectParentInterface) $lhs->setParent($this, "lhs", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getLhs($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->lhs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null lhs.");
		}
		return $this->lhs;
	}
	
	public function setRhs(Expr $rhs = null, $notify = true)
	{
		if ($this->rhs !== $rhs) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->rhs instanceof \RepositoryObjectParentInterface) $this->rhs->setParent(null);
			$this->rhs = $rhs;
			if ($rhs instanceof \RepositoryObjectParentInterface) $rhs->setParent($this, "rhs", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getRhs($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->rhs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null rhs.");
		}
		return $this->rhs;
	}
	
	public function setOperator($operator, $notify = true)
	{
		if (!is_string($operator)) {
			throw new \InvalidArgumentException("operator needs to be a string");
		}
		if ($this->operator !== $operator) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			$this->operator = $operator;
			if ($notify) {
				$this->notifyFragmentDirty('main');
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
	
	public function setGraphPrev(\RepositoryObjectReference $graphPrev = null, $notify = true)
	{
		if ($this->graphPrev !== $graphPrev) {
			if (!$this->graph_loaded) {
				$this->loadFragment('graph');
			}
			if ($this->graphPrev instanceof \RepositoryObjectParentInterface) $this->graphPrev->setParent(null);
			$this->graphPrev = $graphPrev;
			if ($graphPrev instanceof \RepositoryObjectParentInterface) $graphPrev->setParent($this, "graphPrev", "graph");
			if ($notify) {
				$this->notifyFragmentDirty('graph');
			}
		}
	}
	public function getGraphPrev($enforce = true)
	{
		if (!$this->graph_loaded) {
			$this->loadFragment('graph');
		}
		if ($enforce && $this->graphPrev === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null graphPrev.");
		}
		return $this->graphPrev;
	}
	
	public function setCallName($callName, $notify = true)
	{
		if (!is_string($callName)) {
			throw new \InvalidArgumentException("callName needs to be a string");
		}
		if ($this->callName !== $callName) {
			if (!$this->call_loaded) {
				$this->loadFragment('call');
			}
			$this->callName = $callName;
			if ($notify) {
				$this->notifyFragmentDirty('call');
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
	
	public function setCallArguments(CallArgumentTuple $callArguments = null, $notify = true)
	{
		if ($this->callArguments !== $callArguments) {
			if (!$this->call_loaded) {
				$this->loadFragment('call');
			}
			if ($this->callArguments instanceof \RepositoryObjectParentInterface) $this->callArguments->setParent(null);
			$this->callArguments = $callArguments;
			if ($callArguments instanceof \RepositoryObjectParentInterface) $callArguments->setParent($this, "callArguments", "call");
			if ($notify) {
				$this->notifyFragmentDirty('call');
			}
		}
	}
	public function getCallArguments($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->callArguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null callArguments.");
		}
		return $this->callArguments;
	}
}