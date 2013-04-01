<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class TypeExpr extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = false;
	protected $expr;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("tree");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "expr", "type" => "Expr"));
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
			if ($this->expr instanceof \RepositoryNodeObject) $this->expr->setParent(null);
			$this->expr = $expr;
			if ($expr instanceof \RepositoryNodeObject) $expr->setParent($this, "expr", "tree");
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
}