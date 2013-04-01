<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionArgument extends \RepositoryNodeObject
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
				array("name" => "typeExpr", "type" => "TypeExpr"));
			case "main": return array(
				array("name" => "name", "type" => "string"));
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
			if ($this->typeExpr instanceof \RepositoryNodeObject) $this->typeExpr->setParent(null);
			$this->typeExpr = $typeExpr;
			if ($typeExpr instanceof \RepositoryNodeObject) $typeExpr->setParent($this, "typeExpr", "tree");
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
			if ($this->name instanceof \RepositoryNodeObject) $this->name->setParent(null);
			$this->name = $name;
			if ($name instanceof \RepositoryNodeObject) $name->setParent($this, "name", "main");
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