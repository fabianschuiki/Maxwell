<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class IdentifierExpr extends Expr implements RangeInterface, GraphInterface, BindingInterface, TypeInterface, ExprCodeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = true;
	protected $range;
	protected $humanRange;
	protected $name;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	// binding fragment
	public $binding_dirty  = false;
	public $binding_loaded = true;
	protected $bindingTarget;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $possibleType;
	protected $someText;
	
	// code fragment
	public $code_dirty  = false;
	public $code_loaded = true;
	protected $exprCode;
	protected $stmtsCode;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent = null, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("main","graph","binding","type","code");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "binding": return array(
				array("name" => "bindingTarget", "type" => "\RepositoryObjectReference"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "someText", "type" => "string"));
			case "code": return array(
				array("name" => "exprCode", "type" => "string"), 
				array("name" => "stmtsCode", "type" => "string"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "IdentifierExpr";
	}
	
	
	/* ACCESSORS */
	public function setRange(\Source\Range $range = null, $notify = true)
	{
		if ($this->range !== $range) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->range instanceof \RepositoryObjectParentInterface) $this->range->setParent(null);
			$this->range = $range;
			if ($range instanceof \RepositoryObjectParentInterface) $range->setParent($this, "range", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getRange($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->range === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null range.");
		}
		return $this->range;
	}
	
	public function setHumanRange(\Source\Range $humanRange = null, $notify = true)
	{
		if ($this->humanRange !== $humanRange) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->humanRange instanceof \RepositoryObjectParentInterface) $this->humanRange->setParent(null);
			$this->humanRange = $humanRange;
			if ($humanRange instanceof \RepositoryObjectParentInterface) $humanRange->setParent($this, "humanRange", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getHumanRange($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->humanRange === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null humanRange.");
		}
		return $this->humanRange;
	}
	
	public function setName($name, $notify = true)
	{
		if (!is_string($name)) {
			throw new \InvalidArgumentException("name needs to be a string");
		}
		if ($this->name !== $name) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			$this->name = $name;
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getName($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->name === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null name.");
		}
		return $this->name;
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
	
	public function setBindingTarget(\RepositoryObjectReference $bindingTarget = null, $notify = true)
	{
		if ($this->bindingTarget !== $bindingTarget) {
			if (!$this->binding_loaded) {
				$this->loadFragment('binding');
			}
			if ($this->bindingTarget instanceof \RepositoryObjectParentInterface) $this->bindingTarget->setParent(null);
			$this->bindingTarget = $bindingTarget;
			if ($bindingTarget instanceof \RepositoryObjectParentInterface) $bindingTarget->setParent($this, "bindingTarget", "binding");
			if ($notify) {
				$this->notifyFragmentDirty('binding');
			}
		}
	}
	public function getBindingTarget($enforce = true)
	{
		if (!$this->binding_loaded) {
			$this->loadFragment('binding');
		}
		if ($enforce && $this->bindingTarget === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null bindingTarget.");
		}
		return $this->bindingTarget;
	}
	
	public function setPossibleType($possibleType, $notify = true)
	{
		if ($this->possibleType !== $possibleType) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			$this->possibleType = $possibleType;
			if ($notify) {
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
	
	public function setSomeText($someText, $notify = true)
	{
		if (!is_string($someText)) {
			throw new \InvalidArgumentException("someText needs to be a string");
		}
		if ($this->someText !== $someText) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			$this->someText = $someText;
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getSomeText($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->someText === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null someText.");
		}
		return $this->someText;
	}
	
	public function setExprCode($exprCode, $notify = true)
	{
		if (!is_string($exprCode)) {
			throw new \InvalidArgumentException("exprCode needs to be a string");
		}
		if ($this->exprCode !== $exprCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			$this->exprCode = $exprCode;
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getExprCode($enforce = true)
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		if ($enforce && $this->exprCode === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null exprCode.");
		}
		return $this->exprCode;
	}
	
	public function setStmtsCode($stmtsCode, $notify = true)
	{
		if (!is_string($stmtsCode)) {
			throw new \InvalidArgumentException("stmtsCode needs to be a string");
		}
		if ($this->stmtsCode !== $stmtsCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			$this->stmtsCode = $stmtsCode;
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getStmtsCode($enforce = true)
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		if ($enforce && $this->stmtsCode === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null stmtsCode.");
		}
		return $this->stmtsCode;
	}
}