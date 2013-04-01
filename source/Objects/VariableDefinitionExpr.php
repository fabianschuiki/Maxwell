<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class VariableDefinitionExpr extends \RepositoryNodeObject implements Expr, RangeInterface, TypeInterface, ExprCodeInterface
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
	protected $typeExpr;
	protected $initialExpr;
	
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
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("main","type","code");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => "string"), 
				array("name" => "typeExpr", "type" => "TypeExpr"), 
				array("name" => "initialExpr", "type" => "Expr"));
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
		return "VariableDefinitionExpr";
	}
	
	
	/* ACCESSORS */
	public function setRange(\Source\Range $range = null, $notify = true)
	{
		if ($this->range !== $range) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			$this->range = $range;
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
			$this->humanRange = $humanRange;
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
			$this->name = $name;
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
	
	public function setTypeExpr(TypeExpr $typeExpr = null, $notify = true)
	{
		if ($this->typeExpr !== $typeExpr) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			$this->typeExpr = $typeExpr;
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getTypeExpr()
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		return $this->typeExpr;
	}
	
	public function setInitialExpr(Expr $initialExpr = null, $notify = true)
	{
		if ($this->initialExpr !== $initialExpr) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			$this->initialExpr = $initialExpr;
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getInitialExpr()
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		return $this->initialExpr;
	}
	
	public function setType(Type $type = null, $notify = true)
	{
		if ($this->type !== $type) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			$this->type = $type;
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
			$this->stmtsCode = $stmtsCode;
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