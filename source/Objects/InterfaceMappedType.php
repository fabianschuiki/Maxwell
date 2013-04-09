<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class InterfaceMappedType extends \RepositoryNodeObject implements \EqualInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $type;
	protected $interface;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	
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
		return array("main","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "type", "type" => ""), 
				array("name" => "interface", "type" => ""));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "InterfaceMappedType";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of InterfaceMappedType as well.');
		}
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->type, $x->type)) {
			$this->println(0, "Change detected in type");
			return false;
		}
		if (!$this->areEqual($this->interface, $x->interface)) {
			$this->println(0, "Change detected in interface");
			return false;
		}
	
		// graph fragment
		if (!$this->graph_loaded) {
			$this->loadFragment("graph");
		}
		if (!$this->areEqual($this->graphPrev, $x->graphPrev)) {
			$this->println(0, "Change detected in graphPrev");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setType($type, $notify = true)
	{
		if (!$this->areEqual($this->type, $type)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->type instanceof \RepositoryObjectParentInterface) {
				$this->type->setParent(null);
			}
			if ($type instanceof \RepositoryObjectParentInterface) {
				$type->setParent($this, "type", "main");
			}
			$this->type = $type;
			if ($notify) {
				$this->notifyObjectDirty("type");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setTypeRef($type, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($type instanceof \RepositoryObjectReference) {
			$v->set($type->getRefId());
		} else {
			$v->set($type);
		}
		$this->setType($v, $notify);
	}
	public function getType($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->type === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null type.");
		}
		if ($unref && $this->type instanceof \RepositoryObjectReference) {
			$v = $this->type->get();
		} else {
			$v = $this->type;
		}
		return $v;
	}
	
	public function setInterface($interface, $notify = true)
	{
		if (!$this->areEqual($this->interface, $interface)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->interface instanceof \RepositoryObjectParentInterface) {
				$this->interface->setParent(null);
			}
			if ($interface instanceof \RepositoryObjectParentInterface) {
				$interface->setParent($this, "interface", "main");
			}
			$this->interface = $interface;
			if ($notify) {
				$this->notifyObjectDirty("interface");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setInterfaceRef($interface, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($interface instanceof \RepositoryObjectReference) {
			$v->set($interface->getRefId());
		} else {
			$v->set($interface);
		}
		$this->setInterface($v, $notify);
	}
	public function getInterface($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->interface === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null interface.");
		}
		if ($unref && $this->interface instanceof \RepositoryObjectReference) {
			$v = $this->interface->get();
		} else {
			$v = $this->interface;
		}
		return $v;
	}
	
	public function setGraphPrev($graphPrev, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->graphPrev, $graphPrev)) {
			if (!$this->graph_loaded) {
				$this->loadFragment("graph");
			}
			if ($this->graphPrev instanceof \RepositoryObjectParentInterface) {
				$this->graphPrev->setParent(null);
			}
			if ($graphPrev instanceof \RepositoryObjectParentInterface) {
				$graphPrev->setParent($this, "graphPrev", "graph");
			}
			$this->graphPrev = $graphPrev;
			if ($notify) {
				$this->notifyObjectDirty("graphPrev");
				$this->notifyFragmentDirty("graph");
			}
		}
	}
	public function setGraphPrevRef($graphPrev, \Repository $repository, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($graphPrev instanceof \RepositoryObjectReference) {
			$v->set($graphPrev->getRefId());
		} else {
			$v->set($graphPrev);
		}
		$this->setGraphPrev($v, $notify);
	}
	public function getGraphPrev($enforce = true, $unref = true)
	{
		if (!$this->graph_loaded) {
			$this->loadFragment('graph');
		}
		if ($enforce && $this->graphPrev === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null graphPrev.");
		}
		if ($unref && $this->graphPrev instanceof \RepositoryObjectReference) {
			$v = $this->graphPrev->get();
		} else {
			$v = $this->graphPrev;
		}
		return $v;
	}
}