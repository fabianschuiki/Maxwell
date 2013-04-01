<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class IdentifierExpr extends \RepositoryNodeObject implements RangeInterface, BindingInterface, TypeInterface, ExprCodeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $range;
	protected $humanRange;
	protected $name;
	
	// binding fragment
	public $binding_dirty  = false;
	public $binding_loaded = false;
	protected $bindingTarget;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = false;
	protected $type;
	protected $someText;
	
	// code fragment
	public $code_dirty  = false;
	public $code_loaded = false;
	protected $exprCode;
	protected $stmtsCode;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("main","binding","type","code");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => "string"));
			case "binding": return array(
				array("name" => "bindingTarget", "type" => "Expr"));
			case "type": return array(
				array("name" => "type", "type" => "Type"), 
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
			if ($this->range instanceof \RepositoryNodeObject) $this->range->setParent(null);
			$this->range = $range;
			if ($range instanceof \RepositoryNodeObject) $range->setParent($this, "range", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getRange()
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		return $this->range;
	}
	
	public function setHumanRange(\Source\Range $humanRange = null, $notify = true)
	{
		if ($this->humanRange !== $humanRange) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->humanRange instanceof \RepositoryNodeObject) $this->humanRange->setParent(null);
			$this->humanRange = $humanRange;
			if ($humanRange instanceof \RepositoryNodeObject) $humanRange->setParent($this, "humanRange", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getHumanRange()
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
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
			if ($this->name instanceof \RepositoryNodeObject) $this->name->setParent(null);
			$this->name = $name;
			if ($name instanceof \RepositoryNodeObject) $name->setParent($this, "name", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getName()
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		return $this->name;
	}
	
	public function setBindingTarget(Expr $bindingTarget = null, $notify = true)
	{
		if ($this->bindingTarget !== $bindingTarget) {
			if (!$this->binding_loaded) {
				$this->loadFragment('binding');
			}
			if ($this->bindingTarget instanceof \RepositoryNodeObject) $this->bindingTarget->setParent(null);
			$this->bindingTarget = $bindingTarget;
			if ($bindingTarget instanceof \RepositoryNodeObject) $bindingTarget->setParent($this, "bindingTarget", "binding");
			if ($notify) {
				$this->notifyFragmentDirty('binding');
			}
		}
	}
	public function getBindingTarget()
	{
		if (!$this->binding_loaded) {
			$this->loadFragment('binding');
		}
		return $this->bindingTarget;
	}
	
	public function setType(Type $type = null, $notify = true)
	{
		if ($this->type !== $type) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			if ($this->type instanceof \RepositoryNodeObject) $this->type->setParent(null);
			$this->type = $type;
			if ($type instanceof \RepositoryNodeObject) $type->setParent($this, "type", "type");
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getType()
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		return $this->type;
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
			if ($this->someText instanceof \RepositoryNodeObject) $this->someText->setParent(null);
			$this->someText = $someText;
			if ($someText instanceof \RepositoryNodeObject) $someText->setParent($this, "someText", "type");
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getSomeText()
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
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
			if ($this->exprCode instanceof \RepositoryNodeObject) $this->exprCode->setParent(null);
			$this->exprCode = $exprCode;
			if ($exprCode instanceof \RepositoryNodeObject) $exprCode->setParent($this, "exprCode", "code");
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getExprCode()
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
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
			if ($this->stmtsCode instanceof \RepositoryNodeObject) $this->stmtsCode->setParent(null);
			$this->stmtsCode = $stmtsCode;
			if ($stmtsCode instanceof \RepositoryNodeObject) $stmtsCode->setParent($this, "stmtsCode", "code");
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getStmtsCode()
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		return $this->stmtsCode;
	}
}