<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class AssignmentExpr extends Expr implements GraphInterface
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
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("tree","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "lhs", "type" => "Expr"), 
				array("name" => "rhs", "type" => "Expr"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
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
}