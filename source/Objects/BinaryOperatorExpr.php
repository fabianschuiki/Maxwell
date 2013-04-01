<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class BinaryOperatorExpr extends Expr
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = false;
	protected $lhs;
	protected $rhs;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $operator;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("tree","main");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "lhs", "type" => "Expr"), 
				array("name" => "rhs", "type" => "Expr"));
			case "main": return array(
				array("name" => "operator", "type" => "string"));
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
			if ($this->lhs instanceof \RepositoryNodeObject) $this->lhs->setParent(null);
			$this->lhs = $lhs;
			if ($lhs instanceof \RepositoryNodeObject) $lhs->setParent($this, "lhs", "tree");
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
			if ($this->rhs instanceof \RepositoryNodeObject) $this->rhs->setParent(null);
			$this->rhs = $rhs;
			if ($rhs instanceof \RepositoryNodeObject) $rhs->setParent($this, "rhs", "tree");
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
			if ($this->operator instanceof \RepositoryNodeObject) $this->operator->setParent(null);
			$this->operator = $operator;
			if ($operator instanceof \RepositoryNodeObject) $operator->setParent($this, "operator", "main");
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
}