<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class AssignmentExpr extends Expr implements GraphInterface, TypeInterface
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
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $possibleType;
	protected $requiredType;
	protected $actualType;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("tree","graph","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "lhs", "type" => "Expr"), 
				array("name" => "rhs", "type" => "Expr"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "AssignmentExpr";
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
	
	public function setPossibleType($possibleType, $notify = true)
	{
		if ($this->possibleType !== $possibleType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			$this->possibleType = $possibleType;
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getPossibleType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->possibleType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null possibleType.");
		}
		return $this->possibleType;
	}
	
	public function setRequiredType($requiredType, $notify = true)
	{
		if ($this->requiredType !== $requiredType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			$this->requiredType = $requiredType;
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getRequiredType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->requiredType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null requiredType.");
		}
		return $this->requiredType;
	}
	
	public function setActualType($actualType, $notify = true)
	{
		if ($this->actualType !== $actualType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			$this->actualType = $actualType;
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getActualType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->actualType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null actualType.");
		}
		return $this->actualType;
	}
}