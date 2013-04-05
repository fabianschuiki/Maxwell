<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class CastType extends \RepositoryNodeObject
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $from;
	protected $to;
	protected $cost;
	protected $func;
	
	
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
		return array("main");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "from", "type" => ""), 
				array("name" => "to", "type" => ""), 
				array("name" => "cost", "type" => "numeric"), 
				array("name" => "func", "type" => "\AbstractFunction"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "CastType";
	}
	
	
	/* ACCESSORS */
	public function setFrom($from, $notify = true)
	{
		if ($this->hasPropertyChanged($this->from, $from)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->from instanceof \RepositoryObjectParentInterface) {
				$this->from->setParent(null);
			}
			if ($from instanceof \RepositoryObjectParentInterface) {
				$from->setParent($this, "from", "main");
			}
			$this->from = $from;
			if ($notify) {
				$this->notifyObjectDirty("from");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setFromRef($from, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($from instanceof \RepositoryObjectReference) {
			$v->set($from->getRefId());
		} else {
			$v->set($from);
		}
		$this->setFrom($v, $notify);
	}
	public function getFrom($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->from === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null from.");
		}
		if ($unref && $this->from instanceof \RepositoryObjectReference) {
			$v = $this->from->get(!$enforce);
		} else {
			$v = $this->from;
		}
		return $v;
	}
	
	public function setTo($to, $notify = true)
	{
		if ($this->hasPropertyChanged($this->to, $to)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->to instanceof \RepositoryObjectParentInterface) {
				$this->to->setParent(null);
			}
			if ($to instanceof \RepositoryObjectParentInterface) {
				$to->setParent($this, "to", "main");
			}
			$this->to = $to;
			if ($notify) {
				$this->notifyObjectDirty("to");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setToRef($to, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($to instanceof \RepositoryObjectReference) {
			$v->set($to->getRefId());
		} else {
			$v->set($to);
		}
		$this->setTo($v, $notify);
	}
	public function getTo($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->to === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null to.");
		}
		if ($unref && $this->to instanceof \RepositoryObjectReference) {
			$v = $this->to->get(!$enforce);
		} else {
			$v = $this->to;
		}
		return $v;
	}
	
	public function setCost($cost, $notify = true)
	{
		if (!is_numeric($cost)) {
			throw new \InvalidArgumentException("cost needs to be a number");
		}
		if ($this->cost !== $cost) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			$this->cost = $cost;
			if ($notify) {
				$this->notifyObjectDirty("cost");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function getCost($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->cost === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null cost.");
		}
		return $this->cost;
	}
	
	public function setFunc($func, $notify = true)
	{
		if (!$func instanceof \AbstractFunction && !$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \AbstractFunction or \RepositoryObjectReference');
		}
		if ($this->hasPropertyChanged($this->func, $func)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->func instanceof \RepositoryObjectParentInterface) {
				$this->func->setParent(null);
			}
			if ($func instanceof \RepositoryObjectParentInterface) {
				$func->setParent($this, "func", "main");
			}
			$this->func = $func;
			if ($notify) {
				$this->notifyObjectDirty("func");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setFuncRef($func, \Repository $repository, $notify = true)
	{
		if (!$func instanceof \AbstractFunction && !$func instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs func to be an instance of \AbstractFunction or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($func instanceof \RepositoryObjectReference) {
			$v->set($func->getRefId());
		} else {
			$v->set($func);
		}
		$this->setFunc($v, $notify);
	}
	public function getFunc($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->func === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null func.");
		}
		if ($unref && $this->func instanceof \RepositoryObjectReference) {
			$v = $this->func->get(!$enforce);
		} else {
			$v = $this->func;
		}
		return $v;
	}
}