<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class IdentifierExpr extends RepositoryObject implements Expr, RangeInterface, BindingInterface, TypeInterface
{
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
	
	
	public function setRange(Source\Range $range = null)
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
	
	public function setHumanRange(Source\Range $humanRange = null)
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
	
	public function setBindingTarget(Expr $bindingTarget = null)
	{
		if ($this->bindingTarget !== $bindingTarget) {
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
}