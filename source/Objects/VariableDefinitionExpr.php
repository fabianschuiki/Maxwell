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
	public $main_loaded = true;
	protected $range;
	protected $humanRange;
	protected $name;
	protected $typeExpr;
	protected $initialExpr;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $type;
	
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
	
	public function setTypeExpr(TypeExpr $typeExpr = null, $notify = true)
	{
		if ($this->typeExpr !== $typeExpr) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->typeExpr instanceof \RepositoryObjectParentInterface) $this->typeExpr->setParent(null);
			$this->typeExpr = $typeExpr;
			if ($typeExpr instanceof \RepositoryObjectParentInterface) $typeExpr->setParent($this, "typeExpr", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getTypeExpr($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->typeExpr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null typeExpr.");
		}
		return $this->typeExpr;
	}
	
	public function setInitialExpr(Expr $initialExpr = null, $notify = true)
	{
		if ($this->initialExpr !== $initialExpr) {
			if (!$this->main_loaded) {
				$this->loadFragment('main');
			}
			if ($this->initialExpr instanceof \RepositoryObjectParentInterface) $this->initialExpr->setParent(null);
			$this->initialExpr = $initialExpr;
			if ($initialExpr instanceof \RepositoryObjectParentInterface) $initialExpr->setParent($this, "initialExpr", "main");
			if ($notify) {
				$this->notifyFragmentDirty('main');
			}
		}
	}
	public function getInitialExpr($enforce = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->initialExpr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null initialExpr.");
		}
		return $this->initialExpr;
	}
	
	public function setType(Type $type = null, $notify = true)
	{
		if ($this->type !== $type) {
			if (!$this->type_loaded) {
				$this->loadFragment('type');
			}
			if ($this->type instanceof \RepositoryObjectParentInterface) $this->type->setParent(null);
			$this->type = $type;
			if ($type instanceof \RepositoryObjectParentInterface) $type->setParent($this, "type", "type");
			if ($notify) {
				$this->notifyFragmentDirty('type');
			}
		}
	}
	public function getType($enforce = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->type === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null type.");
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