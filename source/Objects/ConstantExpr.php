<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class ConstantExpr extends Expr
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $value;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("main");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "value", "type" => "string"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "ConstantExpr";
	}
	
	
	/* ACCESSORS */
	public function setValue($value, $notify = true)
	{
		if (!is_string($value)) {
			throw new \InvalidArgumentException("value needs to be a string");
		}
		if ($this->value !== $value) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->value instanceof \RepositoryNodeObject) $this->value->setParent(null);
			$this->value = $value;
			if ($value instanceof \RepositoryNodeObject) $value->setParent($this, "value", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getValue()
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		return $this->value;
	}
}