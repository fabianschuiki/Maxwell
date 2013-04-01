<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionDefinition extends \RepositoryRootObject implements RangeInterface, TypeInterface, RootCodeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = false;
	protected $ident;
	
	// main fragment
	public $main_dirty  = false;
	public $main_loaded = false;
	protected $range;
	protected $humanRange;
	protected $name;
	
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
	public function setParent(\RepositoryObject $parent, $key = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
	}
	
	public function getFragmentNames()
	{
		return array("tree","main","type","code");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "ident", "type" => "\Objects\IdentifierExpr"));
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => "string"));
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
	public function setIdent(\Objects\IdentifierExpr $ident = null, $notify = true)
	{
		if ($this->ident !== $ident) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->ident !== null) $this->ident->setParent(null);
			$this->ident = $ident;
			if ($ident !== null) $ident->setParent($this, "ident");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getIdent()
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		return $this->ident;
	}
	
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
	
	public function setIndepDeclCode($indepDeclCode, $notify = true)
	{
		if (!is_string($indepDeclCode)) {
			throw new \InvalidArgumentException("indepDeclCode needs to be a string");
		}
		if ($this->indepDeclCode !== $indepDeclCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			$this->indepDeclCode = $indepDeclCode;
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getIndepDeclCode()
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		return $this->indepDeclCode;
	}
	
	public function setDepDeclCode($depDeclCode, $notify = true)
	{
		if (!is_string($depDeclCode)) {
			throw new \InvalidArgumentException("depDeclCode needs to be a string");
		}
		if ($this->depDeclCode !== $depDeclCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			$this->depDeclCode = $depDeclCode;
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getDepDeclCode()
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		return $this->depDeclCode;
	}
	
	public function setIndepDefCode($indepDefCode, $notify = true)
	{
		if (!is_string($indepDefCode)) {
			throw new \InvalidArgumentException("indepDefCode needs to be a string");
		}
		if ($this->indepDefCode !== $indepDefCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			$this->indepDefCode = $indepDefCode;
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getIndepDefCode()
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		return $this->indepDefCode;
	}
	
	public function setDepDefCode($depDefCode, $notify = true)
	{
		if (!is_string($depDefCode)) {
			throw new \InvalidArgumentException("depDefCode needs to be a string");
		}
		if ($this->depDefCode !== $depDefCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			$this->depDefCode = $depDefCode;
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getDepDefCode()
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		return $this->depDefCode;
	}
}