<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class InheritanceMappedType extends \RepositoryNodeObject implements \EqualInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $type;
	protected $struct;
	protected $inheritance;
	
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
				array("name" => "struct", "type" => ""), 
				array("name" => "inheritance", "type" => ""));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "InheritanceMappedType";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of InheritanceMappedType as well.');
		}
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->type, $x->type)) {
			$this->println(0, "Change detected in type");
			return false;
		}
		if (!$this->areEqual($this->struct, $x->struct)) {
			$this->println(0, "Change detected in struct");
			return false;
		}
		if (!$this->areEqual($this->inheritance, $x->inheritance)) {
			$this->println(0, "Change detected in inheritance");
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
	
	public function setStruct($struct, $notify = true)
	{
		if (!$this->areEqual($this->struct, $struct)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->struct instanceof \RepositoryObjectParentInterface) {
				$this->struct->setParent(null);
			}
			if ($struct instanceof \RepositoryObjectParentInterface) {
				$struct->setParent($this, "struct", "main");
			}
			$this->struct = $struct;
			if ($notify) {
				$this->notifyObjectDirty("struct");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setStructRef($struct, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($struct instanceof \RepositoryObjectReference) {
			$v->set($struct->getRefId());
		} else {
			$v->set($struct);
		}
		$this->setStruct($v, $notify);
	}
	public function getStruct($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->struct === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null struct.");
		}
		if ($unref && $this->struct instanceof \RepositoryObjectReference) {
			$v = $this->struct->get();
		} else {
			$v = $this->struct;
		}
		return $v;
	}
	
	public function setInheritance($inheritance, $notify = true)
	{
		if (!$this->areEqual($this->inheritance, $inheritance)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->inheritance instanceof \RepositoryObjectParentInterface) {
				$this->inheritance->setParent(null);
			}
			if ($inheritance instanceof \RepositoryObjectParentInterface) {
				$inheritance->setParent($this, "inheritance", "main");
			}
			$this->inheritance = $inheritance;
			if ($notify) {
				$this->notifyObjectDirty("inheritance");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setInheritanceRef($inheritance, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($inheritance instanceof \RepositoryObjectReference) {
			$v->set($inheritance->getRefId());
		} else {
			$v->set($inheritance);
		}
		$this->setInheritance($v, $notify);
	}
	public function getInheritance($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->inheritance === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inheritance.");
		}
		if ($unref && $this->inheritance instanceof \RepositoryObjectReference) {
			$v = $this->inheritance->get();
		} else {
			$v = $this->inheritance;
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