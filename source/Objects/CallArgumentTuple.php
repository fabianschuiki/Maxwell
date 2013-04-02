<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallArgumentTuple extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// call fragment
	public $call_dirty  = false;
	public $call_loaded = true;
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
		return array("call");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "call": return array(
				array("name" => "arguments", "type" => "\RepositoryObjectArray"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallArgumentTuple";
	}
	
	
	/* ACCESSORS */
	public function setArguments(\RepositoryObjectArray $arguments = null, $notify = true)
	{
		if ($this->arguments !== $arguments) {
			if (!$this->call_loaded) {
				$this->loadFragment('call');
			}
			if ($this->arguments instanceof \RepositoryObjectParentInterface) $this->arguments->setParent(null);
			$this->arguments = $arguments;
			if ($arguments instanceof \RepositoryObjectParentInterface) $arguments->setParent($this, "arguments", "call");
			if ($notify) {
				$this->notifyFragmentDirty('call');
			}
		}
	}
	public function getArguments($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->arguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null arguments.");
		}
		return $this->arguments;
	}
}