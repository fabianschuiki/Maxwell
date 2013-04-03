<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionArgumentTupleType extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $arguments;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
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
				array("name" => "arguments", "type" => "\RepositoryObjectArray"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionArgumentTupleType";
	}
	
	
	/* ACCESSORS */
	public function setArguments(\RepositoryObjectArray $arguments = null, $notify = true)
	{
		if ($this->arguments !== $arguments) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->arguments instanceof \RepositoryObjectParentInterface) $this->arguments->setParent(null);
			$this->arguments = $arguments;
			if ($arguments instanceof \RepositoryObjectParentInterface) $arguments->setParent($this, "arguments", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getArguments($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->arguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null arguments.");
		}
		return $this->arguments;
	}
}