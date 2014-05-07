<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class Assumption extends \RepositoryNodeObject implements \EqualInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// assumer fragment
	public $assumer_dirty  = false;
	public $assumer_loaded = true;
	protected $target;
	protected $assumption;
	
	
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
		return array("assumer");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "assumer": return array(
				array("name" => "target", "type" => ""), 
				array("name" => "assumption", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "Assumption";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of Assumption as well.');
		}
		// assumer fragment
		if (!$this->assumer_loaded) {
			$this->loadFragment("assumer");
		}
		if (!$this->areEqual($this->target, $x->target)) {
			$this->println(0, "Change detected in target");
			return false;
		}
		if (!$this->areEqual($this->assumption, $x->assumption)) {
			$this->println(0, "Change detected in assumption");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setTarget($target, $notify = true)
	{
		if (!$this->areEqual($this->target, $target)) {
			if (!$this->assumer_loaded) {
				$this->loadFragment("assumer");
			}
			if ($this->target instanceof \RepositoryObjectParentInterface) {
				$this->target->setParent(null);
			}
			if ($target instanceof \RepositoryObjectParentInterface) {
				$target->setParent($this, "target", "assumer");
			}
			$this->target = $target;
			if ($notify) {
				$this->notifyObjectDirty("target");
				$this->notifyFragmentDirty("assumer");
			}
		}
	}
	public function setTargetRef($target, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($target instanceof \RepositoryObjectReference) {
			$v->set($target->getRefId());
		} else {
			$v->set($target);
		}
		$this->setTarget($v, $notify);
	}
	public function getTarget($enforce = true, $unref = true)
	{
		if (!$this->assumer_loaded) {
			$this->loadFragment('assumer');
		}
		if ($enforce && $this->target === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null target.");
		}
		if ($unref && $this->target instanceof \RepositoryObjectReference) {
			$v = $this->target->get();
		} else {
			$v = $this->target;
		}
		return $v;
	}
	
	public function setAssumption($assumption, $notify = true)
	{
		if (!$this->areEqual($this->assumption, $assumption)) {
			if (!$this->assumer_loaded) {
				$this->loadFragment("assumer");
			}
			if ($this->assumption instanceof \RepositoryObjectParentInterface) {
				$this->assumption->setParent(null);
			}
			if ($assumption instanceof \RepositoryObjectParentInterface) {
				$assumption->setParent($this, "assumption", "assumer");
			}
			$this->assumption = $assumption;
			if ($notify) {
				$this->notifyObjectDirty("assumption");
				$this->notifyFragmentDirty("assumer");
			}
		}
	}
	public function setAssumptionRef($assumption, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($assumption instanceof \RepositoryObjectReference) {
			$v->set($assumption->getRefId());
		} else {
			$v->set($assumption);
		}
		$this->setAssumption($v, $notify);
	}
	public function getAssumption($enforce = true, $unref = true)
	{
		if (!$this->assumer_loaded) {
			$this->loadFragment('assumer');
		}
		if ($enforce && $this->assumption === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null assumption.");
		}
		if ($unref && $this->assumption instanceof \RepositoryObjectReference) {
			$v = $this->assumption->get();
		} else {
			$v = $this->assumption;
		}
		return $v;
	}
}