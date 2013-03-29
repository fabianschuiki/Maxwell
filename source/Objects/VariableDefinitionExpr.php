<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class VariableDefinitionExpr extends \RepositoryObject implements Expr, RangeInterface, TypeInterface, ExprCodeInterface
{
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
	
	
	public function setRange(\Source\Range $range = null)
	{
		if ($this->range !== $range) {
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
		if ($this->name !== $name) {
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
	
	public function setTypeExpr(TypeExpr $typeExpr = null)
	{
		if ($this->typeExpr !== $typeExpr) {
			$this->typeExpr = $typeExpr;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getTypeExpr()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->typeExpr;
	}
	
	public function setInitialExpr(Expr $initialExpr = null)
	{
		if ($this->initialExpr !== $initialExpr) {
			$this->initialExpr = $initialExpr;
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getInitialExpr()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->initialExpr;
	}
	
	public function setType(Type $type = null)
	{
		if ($this->type !== $type) {
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