<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionDefinition extends \RepositoryRootObject implements RangeInterface, TypeInterface, RootCodeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = false;
	protected $inputs;
	protected $outputs;
	protected $body;
	
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
	public function setParent(\RepositoryObject $parent, $key = null, $fragment = null)
	{
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function getFragmentNames()
	{
		return array("tree","main","type","code");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "inputs", "type" => "\Objects\FunctionArgumentTuple"), 
				array("name" => "outputs", "type" => "\Objects\FunctionArgumentTuple"), 
				array("name" => "body", "type" => "\Objects\FunctionBody"));
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
	public function setInputs(\Objects\FunctionArgumentTuple $inputs = null, $notify = true)
	{
		if ($this->inputs !== $inputs) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->inputs instanceof \RepositoryNodeObject) $this->inputs->setParent(null);
			$this->inputs = $inputs;
			if ($inputs instanceof \RepositoryNodeObject) $inputs->setParent($this, "inputs", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getInputs($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->inputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inputs.");
		}
		return $this->inputs;
	}
	
	public function setOutputs(\Objects\FunctionArgumentTuple $outputs = null, $notify = true)
	{
		if ($this->outputs !== $outputs) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->outputs instanceof \RepositoryNodeObject) $this->outputs->setParent(null);
			$this->outputs = $outputs;
			if ($outputs instanceof \RepositoryNodeObject) $outputs->setParent($this, "outputs", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getOutputs($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->outputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null outputs.");
		}
		return $this->outputs;
	}
	
	public function setBody(\Objects\FunctionBody $body = null, $notify = true)
	{
		if ($this->body !== $body) {
			if (!$this->tree_loaded) {
				$this->loadFragment('tree');
			}
			if ($this->body instanceof \RepositoryNodeObject) $this->body->setParent(null);
			$this->body = $body;
			if ($body instanceof \RepositoryNodeObject) $body->setParent($this, "body", "tree");
			if ($notify) {
				$this->notifyFragmentDirty('tree');
			}
		}
	}
	public function getBody($enforce = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->body === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null body.");
		}
		return $this->body;
	}
	
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
			if ($this->humanRange instanceof \RepositoryNodeObject) $this->humanRange->setParent(null);
			$this->humanRange = $humanRange;
			if ($humanRange instanceof \RepositoryNodeObject) $humanRange->setParent($this, "humanRange", "main");
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
			if ($this->name instanceof \RepositoryNodeObject) $this->name->setParent(null);
			$this->name = $name;
			if ($name instanceof \RepositoryNodeObject) $name->setParent($this, "name", "main");
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
	
	public function setIndepDeclCode($indepDeclCode, $notify = true)
	{
		if (!is_string($indepDeclCode)) {
			throw new \InvalidArgumentException("indepDeclCode needs to be a string");
		}
		if ($this->indepDeclCode !== $indepDeclCode) {
			if (!$this->code_loaded) {
				$this->loadFragment('code');
			}
			if ($this->indepDeclCode instanceof \RepositoryNodeObject) $this->indepDeclCode->setParent(null);
			$this->indepDeclCode = $indepDeclCode;
			if ($indepDeclCode instanceof \RepositoryNodeObject) $indepDeclCode->setParent($this, "indepDeclCode", "code");
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getIndepDeclCode($enforce = true)
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		if ($enforce && $this->indepDeclCode === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null indepDeclCode.");
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
			if ($this->depDeclCode instanceof \RepositoryNodeObject) $this->depDeclCode->setParent(null);
			$this->depDeclCode = $depDeclCode;
			if ($depDeclCode instanceof \RepositoryNodeObject) $depDeclCode->setParent($this, "depDeclCode", "code");
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getDepDeclCode($enforce = true)
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		if ($enforce && $this->depDeclCode === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null depDeclCode.");
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
			if ($this->indepDefCode instanceof \RepositoryNodeObject) $this->indepDefCode->setParent(null);
			$this->indepDefCode = $indepDefCode;
			if ($indepDefCode instanceof \RepositoryNodeObject) $indepDefCode->setParent($this, "indepDefCode", "code");
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getIndepDefCode($enforce = true)
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		if ($enforce && $this->indepDefCode === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null indepDefCode.");
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
			if ($this->depDefCode instanceof \RepositoryNodeObject) $this->depDefCode->setParent(null);
			$this->depDefCode = $depDefCode;
			if ($depDefCode instanceof \RepositoryNodeObject) $depDefCode->setParent($this, "depDefCode", "code");
			if ($notify) {
				$this->notifyFragmentDirty('code');
			}
		}
	}
	public function getDepDefCode($enforce = true)
	{
		if (!$this->code_loaded) {
			$this->loadFragment('code');
		}
		if ($enforce && $this->depDefCode === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null depDefCode.");
		}
		return $this->depDefCode;
	}
}