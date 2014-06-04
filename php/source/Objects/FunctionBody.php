<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionBody extends \RepositoryNodeObject implements \EqualInterface
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
			throw new \RuntimeException("Setting parent to {$parent->getId()} when object already has parent {$this->parent->getId()} (".get_class($this->parent).").");
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
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of FunctionBody as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->stmts, $x->stmts)) {
			$this->println(0, "Change detected in stmts");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setStmts($stmts, $notify = true)
	{
		if (!$stmts instanceof \RepositoryObjectArray && !$stmts instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs stmts to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->stmts, $stmts)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->stmts instanceof \RepositoryObjectParentInterface) {
				$this->stmts->setParent(null);
			}
			if ($stmts instanceof \RepositoryObjectParentInterface) {
				$stmts->setParent($this, "stmts", "tree");
			}
			$this->stmts = $stmts;
			if ($notify) {
				$this->notifyObjectDirty("stmts");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setStmtsRef($stmts, \Repository $repository, $notify = true)
	{
		if (!$stmts instanceof \RepositoryObjectArray && !$stmts instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs stmts to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($stmts instanceof \RepositoryObjectReference) {
			$v->set($stmts->getRefId());
		} else {
			$v->set($stmts);
		}
		$this->setStmts($v, $notify);
	}
	public function getStmts($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->stmts === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null stmts.");
		}
		if ($unref && $this->stmts instanceof \RepositoryObjectReference) {
			$v = $this->stmts->get();
		} else {
			$v = $this->stmts;
		}
		return $v;
	}
}