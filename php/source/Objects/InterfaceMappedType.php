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
	protected $from;
	protected $to;
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
				array("name" => "from", "type" => ""), 
				array("name" => "to", "type" => ""), 
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
		if (!$this->areEqual($this->from, $x->from)) {
			$this->println(0, "Change detected in from");
			return false;
		}
		if (!$this->areEqual($this->to, $x->to)) {
			$this->println(0, "Change detected in to");
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
	public function setFrom($from, $notify = true)
	{
		if (!$this->areEqual($this->from, $from)) {
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
			$v = $this->from->get();
		} else {
			$v = $this->from;
		}
		return $v;
	}
	
	public function setTo($to, $notify = true)
	{
		if (!$this->areEqual($this->to, $to)) {
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
			$v = $this->to->get();
		} else {
			$v = $this->to;
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