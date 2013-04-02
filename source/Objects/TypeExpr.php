<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class TypeExpr extends \RepositoryNodeObject implements GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $expr;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
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
				array("name" => "expr", "type" => "Expr"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "TypeExpr";
	}
	
	
	/* ACCESSORS */
	public function setExpr(Expr $expr = null, $notify = true)
	{
		if ($this->expr !== $expr) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->expr instanceof \RepositoryObjectParentInterface) $this->expr->setParent(null);
			$this->expr = $expr;
			if ($expr instanceof \RepositoryObjectParentInterface) $expr->setParent($this, "expr", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getExpr($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->expr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null expr.");
		}
		return $this->expr;
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