<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallArgumentTuple extends \RepositoryNodeObject implements \EqualInterface
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
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of CallArgumentTuple as well.');
		}
		// call fragment
		if (!$this->call_loaded) {
			$this->loadFragment("call");
		}
		if (!$this->areEqual($this->arguments, $x->arguments)) {
			$this->println(0, "Change detected in arguments");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setArguments($arguments, $notify = true)
	{
		if (!$arguments instanceof \RepositoryObjectArray && !$arguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs arguments to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->arguments, $arguments)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->arguments instanceof \RepositoryObjectParentInterface) {
				$this->arguments->setParent(null);
			}
			if ($arguments instanceof \RepositoryObjectParentInterface) {
				$arguments->setParent($this, "arguments", "call");
			}
			$this->arguments = $arguments;
			if ($notify) {
				$this->notifyObjectDirty("arguments");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setArgumentsRef($arguments, \Repository $repository, $notify = true)
	{
		if (!$arguments instanceof \RepositoryObjectArray && !$arguments instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs arguments to be an instance of \RepositoryObjectArray or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($arguments instanceof \RepositoryObjectReference) {
			$v->set($arguments->getRefId());
		} else {
			$v->set($arguments);
		}
		$this->setArguments($v, $notify);
	}
	public function getArguments($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->arguments === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null arguments.");
		}
		if ($unref && $this->arguments instanceof \RepositoryObjectReference) {
			$v = $this->arguments->get();
		} else {
			$v = $this->arguments;
		}
		return $v;
	}
}