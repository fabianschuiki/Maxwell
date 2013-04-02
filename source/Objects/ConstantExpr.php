<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class ConstantExpr extends Expr implements GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $value;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = false;
	protected $graphPrev;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("main","graph");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "value", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
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
}