<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class IdentifierExpr extends \RepositoryObject implements RangeInterface, BindingInterface, TypeInterface, ExprCodeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_name;
	
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
	
	// code fragment
	public $code_dirty  = false;
	public $code_loaded = false;
	protected $exprCode;
	protected $stmtsCode;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $name = null)
	{
		$this->parent = $parent;
		$this->parent_name = $name;
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
				array("name" => "type", "type" => "Type"));
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
	public function setRange(\Source\Range $range = null)
	{
		if ($this->range !== $range) {
			if (!$this->main_loaded) {
				$this->repository->loadObjectFragment($this, 'main');
			}
			$this->range = $range;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getRange()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->range;
	}
	
	public function setHumanRange(\Source\Range $humanRange = null)
	{
		if ($this->humanRange !== $humanRange) {
			if (!$this->main_loaded) {
				$this->repository->loadObjectFragment($this, 'main');
			}
			$this->humanRange = $humanRange;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getHumanRange()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->humanRange;
	}
	
	public function setName($name)
	{
		if (!is_string($name)) {
			throw new \InvalidArgumentException("name needs to be a string");
		}
		if ($this->name !== $name) {
			if (!$this->main_loaded) {
				$this->repository->loadObjectFragment($this, 'main');
			}
			$this->name = $name;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getName()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->name;
	}
	
	public function setBindingTarget(Expr $bindingTarget = null)
	{
		if ($this->bindingTarget !== $bindingTarget) {
			if (!$this->binding_loaded) {
				$this->repository->loadObjectFragment($this, 'binding');
			}
			$this->bindingTarget = $bindingTarget;
			$this->binding_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'binding');
		}
	}
	public function getBindingTarget()
	{
		if (!$this->binding_loaded) {
			$this->repository->loadObjectFragment($this, 'binding');
		}
		return $this->bindingTarget;
	}
	
	public function setType(Type $type = null)
	{
		if ($this->type !== $type) {
			if (!$this->type_loaded) {
				$this->repository->loadObjectFragment($this, 'type');
			}
			$this->type = $type;
			$this->type_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'type');
		}
	}
	public function getType()
	{
		if (!$this->type_loaded) {
			$this->repository->loadObjectFragment($this, 'type');
		}
		return $this->type;
	}
	
	public function setExprCode($exprCode)
	{
		if (!is_string($exprCode)) {
			throw new \InvalidArgumentException("exprCode needs to be a string");
		}
		if ($this->exprCode !== $exprCode) {
			if (!$this->code_loaded) {
				$this->repository->loadObjectFragment($this, 'code');
			}
			$this->exprCode = $exprCode;
			$this->code_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'code');
		}
	}
	public function getExprCode()
	{
		if (!$this->code_loaded) {
			$this->repository->loadObjectFragment($this, 'code');
		}
		return $this->exprCode;
	}
	
	public function setStmtsCode($stmtsCode)
	{
		if (!is_string($stmtsCode)) {
			throw new \InvalidArgumentException("stmtsCode needs to be a string");
		}
		if ($this->stmtsCode !== $stmtsCode) {
			if (!$this->code_loaded) {
				$this->repository->loadObjectFragment($this, 'code');
			}
			$this->stmtsCode = $stmtsCode;
			$this->code_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'code');
		}
	}
	public function getStmtsCode()
	{
		if (!$this->code_loaded) {
			$this->repository->loadObjectFragment($this, 'code');
		}
		return $this->stmtsCode;
	}
}