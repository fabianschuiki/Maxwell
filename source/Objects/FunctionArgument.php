<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionArgument extends \RepositoryNodeObject implements GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = false;
	protected $typeExpr;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $name;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = false;
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
		return array("tree","main","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "typeExpr", "type" => "TypeExpr"));
			case "main": return array(
				array("name" => "name", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionArgument";
	}
	
	
	/* ACCESSORS */
	public function setTypeExpr(TypeExpr $typeExpr = null, $notify = true)
	{
		if ($this->typeExpr !== $typeExpr) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->typeExpr instanceof \RepositoryObjectParentInterface) $this->typeExpr->setParent(null);
			$this->typeExpr = $typeExpr;
			if ($typeExpr instanceof \RepositoryObjectParentInterface) $typeExpr->setParent($this, "typeExpr", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getTypeExpr($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->typeExpr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null typeExpr.");
		}
		return $this->typeExpr;
	}
	
	public function setName($name, $notify = true)
	{
		if (!is_string($name)) {
			throw new \InvalidArgumentException("name needs to be a string");
		}
		if ($this->name !== $name) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			$this->name = $name;
			if ($notify) {
				$this->notifyFragmentDirty('main');
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