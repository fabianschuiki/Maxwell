<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CallArgument extends \RepositoryNodeObject implements \EqualInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// call fragment
	public $call_dirty  = false;
	public $call_loaded = true;
	protected $expr;
	protected $name;
	
	
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
		return array("call");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "call": return array(
				array("name" => "expr", "type" => ""), 
				array("name" => "name", "type" => "string"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CallArgument";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of CallArgument as well.');
		}
		// call fragment
		if (!$this->call_loaded) {
			$this->loadFragment("call");
		}
		if (!$this->areEqual($this->expr, $x->expr)) {
			$this->println(0, "Change detected in expr");
			return false;
		}
		if ($this->name !== $x->name) {
			$this->println(0, "Change detected in name");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setExpr($expr, $notify = true)
	{
		if (!$this->areEqual($this->expr, $expr)) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			if ($this->expr instanceof \RepositoryObjectParentInterface) {
				$this->expr->setParent(null);
			}
			if ($expr instanceof \RepositoryObjectParentInterface) {
				$expr->setParent($this, "expr", "call");
			}
			$this->expr = $expr;
			if ($notify) {
				$this->notifyObjectDirty("expr");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function setExprRef($expr, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($expr instanceof \RepositoryObjectReference) {
			$v->set($expr->getRefId());
		} else {
			$v->set($expr);
		}
		$this->setExpr($v, $notify);
	}
	public function getExpr($enforce = true, $unref = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->expr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null expr.");
		}
		if ($unref && $this->expr instanceof \RepositoryObjectReference) {
			$v = $this->expr->get();
		} else {
			$v = $this->expr;
		}
		return $v;
	}
	
	public function setName($name, $notify = true)
	{
		if (!is_string($name)) {
			throw new \InvalidArgumentException("name needs to be a string");
		}
		if ($this->name !== $name) {
			if (!$this->call_loaded) {
				$this->loadFragment("call");
			}
			$this->name = $name;
			if ($notify) {
				$this->notifyObjectDirty("name");
				$this->notifyFragmentDirty("call");
			}
		}
	}
	public function getName($enforce = true)
	{
		if (!$this->call_loaded) {
			$this->loadFragment('call');
		}
		if ($enforce && $this->name === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null name.");
		}
		return $this->name;
	}
}