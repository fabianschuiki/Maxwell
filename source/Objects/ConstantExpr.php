<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class ConstantExpr extends Expr implements GraphInterface, TypeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $value;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $possibleType;
	protected $requiredType;
	protected $actualType;
	
	
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
		return array("main","graph","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "value", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
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
			$this->value = $value;
			if ($notify) {
				$this->notifyObjectDirty('value');
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getValue($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->value === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null value.");
		}
		return $this->value;
	}
	
	public function setGraphPrev(\RepositoryObjectReference $graphPrev = null, $notify = true)
	{
		if ($this->graphPrev !== $graphPrev) {
			if (!$this->graph_loaded) {
				$this->loadFragment('graph');
			}
			if ($this->graphPrev instanceof \RepositoryObjectParentInterface) $this->graphPrev->setParent(null);
			$this->graphPrev = $graphPrev;
			if ($graphPrev instanceof \RepositoryObjectParentInterface) $graphPrev->setParent($this, "graphPrev", "graph");
			if ($notify) {
				$this->notifyObjectDirty('graphPrev');
				$this->notifyFragmentDirty('graph');
			}
		}
	}
	public function getGraphPrev($enforce = true)
	{
		if (!$this->graph_loaded) {
			$this->loadFragment('graph');
		}
		if ($enforce && $this->graphPrev === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null graphPrev.");
		}
		return $this->graphPrev;
	}
	
	public function setPossibleType($possibleType, $notify = true)
	{
		if ($this->possibleType !== $possibleType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			if ($this->possibleType instanceof \RepositoryObjectParentInterface) $this->possibleType->setParent(null);
			$this->possibleType = $possibleType;
			if ($possibleType instanceof \RepositoryObjectParentInterface) $possibleType->setParent($this, "possibleType", "type");
			if ($notify) {
				$this->notifyObjectDirty('possibleType');
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getPossibleType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->possibleType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null possibleType.");
		}
		return $this->possibleType;
	}
	
	public function setRequiredType($requiredType, $notify = true)
	{
		if ($this->requiredType !== $requiredType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			if ($this->requiredType instanceof \RepositoryObjectParentInterface) $this->requiredType->setParent(null);
			$this->requiredType = $requiredType;
			if ($requiredType instanceof \RepositoryObjectParentInterface) $requiredType->setParent($this, "requiredType", "type");
			if ($notify) {
				$this->notifyObjectDirty('requiredType');
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getRequiredType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->requiredType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null requiredType.");
		}
		return $this->requiredType;
	}
	
	public function setActualType($actualType, $notify = true)
	{
		if ($this->actualType !== $actualType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			if ($this->actualType instanceof \RepositoryObjectParentInterface) $this->actualType->setParent(null);
			$this->actualType = $actualType;
			if ($actualType instanceof \RepositoryObjectParentInterface) $actualType->setParent($this, "actualType", "type");
			if ($notify) {
				$this->notifyObjectDirty('actualType');
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getActualType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->actualType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null actualType.");
		}
		return $this->actualType;
	}
}