<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionDefinition extends \RepositoryRootObject implements RangeInterface, TypeInterface, RootCodeInterface
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
	protected $ident;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = false;
	protected $type;
	
	// code fragment
	public $code_dirty  = false;
	public $code_loaded = false;
	protected $indepDeclCode;
	protected $depDeclCode;
	protected $indepDefCode;
	protected $depDefCode;
	
	
	/* GENERAL */
	public function setParent(\RepositoryObject $parent, $name = null)
	{
		$this->parent = $parent;
		$this->parent_name = $name;
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
				array("name" => "ident", "type" => "\Objects\IdentifierExpr"));
			case "type": return array(
				array("name" => "type", "type" => "Type"));
			case "code": return array(
				array("name" => "indepDeclCode", "type" => "string"), 
				array("name" => "depDeclCode", "type" => "string"), 
				array("name" => "indepDefCode", "type" => "string"), 
				array("name" => "depDefCode", "type" => "string"));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionDefinition";
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
	
	public function setIdent(\Objects\IdentifierExpr $ident = null)
	{
		if ($this->ident !== $ident) {
			if (!$this->main_loaded) {
				$this->repository->loadObjectFragment($this, 'main');
			}
			if ($this->ident !== null) $this->ident->setParent(null);
			$this->ident = $ident;
			if ($ident !== null) $ident->setParent($this, "ident");
			$this->main_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'main');
		}
	}
	public function getIdent()
	{
		if (!$this->main_loaded) {
			$this->repository->loadObjectFragment($this, 'main');
		}
		return $this->ident;
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
	
	public function setIndepDeclCode($indepDeclCode)
	{
		if (!is_string($indepDeclCode)) {
			throw new \InvalidArgumentException("indepDeclCode needs to be a string");
		}
		if ($this->indepDeclCode !== $indepDeclCode) {
			if (!$this->code_loaded) {
				$this->repository->loadObjectFragment($this, 'code');
			}
			$this->indepDeclCode = $indepDeclCode;
			$this->code_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'code');
		}
	}
	public function getIndepDeclCode()
	{
		if (!$this->code_loaded) {
			$this->repository->loadObjectFragment($this, 'code');
		}
		return $this->indepDeclCode;
	}
	
	public function setDepDeclCode($depDeclCode)
	{
		if (!is_string($depDeclCode)) {
			throw new \InvalidArgumentException("depDeclCode needs to be a string");
		}
		if ($this->depDeclCode !== $depDeclCode) {
			if (!$this->code_loaded) {
				$this->repository->loadObjectFragment($this, 'code');
			}
			$this->depDeclCode = $depDeclCode;
			$this->code_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'code');
		}
	}
	public function getDepDeclCode()
	{
		if (!$this->code_loaded) {
			$this->repository->loadObjectFragment($this, 'code');
		}
		return $this->depDeclCode;
	}
	
	public function setIndepDefCode($indepDefCode)
	{
		if (!is_string($indepDefCode)) {
			throw new \InvalidArgumentException("indepDefCode needs to be a string");
		}
		if ($this->indepDefCode !== $indepDefCode) {
			if (!$this->code_loaded) {
				$this->repository->loadObjectFragment($this, 'code');
			}
			$this->indepDefCode = $indepDefCode;
			$this->code_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'code');
		}
	}
	public function getIndepDefCode()
	{
		if (!$this->code_loaded) {
			$this->repository->loadObjectFragment($this, 'code');
		}
		return $this->indepDefCode;
	}
	
	public function setDepDefCode($depDefCode)
	{
		if (!is_string($depDefCode)) {
			throw new \InvalidArgumentException("depDefCode needs to be a string");
		}
		if ($this->depDefCode !== $depDefCode) {
			if (!$this->code_loaded) {
				$this->repository->loadObjectFragment($this, 'code');
			}
			$this->depDefCode = $depDefCode;
			$this->code_dirty = true;
			$this->repository->notifyObjectFragmentDirty($this, 'code');
		}
	}
	public function getDepDefCode()
	{
		if (!$this->code_loaded) {
			$this->repository->loadObjectFragment($this, 'code');
		}
		return $this->depDefCode;
	}
}