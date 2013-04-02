<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallArgument extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $expr;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $name;
	
	
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
				array("name" => "expr", "type" => ""));
			case "main": return array(
				array("name" => "name", "type" => "string"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallArgument";
	}
	
	
	/* ACCESSORS */
	public function setExpr($expr, $notify = true)
	{
		if ($this->expr !== $expr) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			$this->expr = $expr;
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
}