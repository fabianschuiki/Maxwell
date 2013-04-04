<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionBody extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $stmts;
	
	
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
		return array("tree");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "stmts", "type" => "\RepositoryObjectArray"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionBody";
	}
	
	
	/* ACCESSORS */
	public function setStmts(\RepositoryObjectArray $stmts = null, $notify = true)
	{
		if ($this->stmts !== $stmts) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->stmts instanceof \RepositoryObjectParentInterface) $this->stmts->setParent(null);
			$this->stmts = $stmts;
			if ($stmts instanceof \RepositoryObjectParentInterface) $stmts->setParent($this, "stmts", "tree");
			if ($notify) {
				$this->notifyObjectDirty('stmts');
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getStmts($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->stmts === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null stmts.");
		}
		return $this->stmts;
	}
}