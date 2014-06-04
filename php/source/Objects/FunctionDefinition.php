<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class FunctionDefinition extends \RepositoryRootObject implements \AbstractFunction, \EqualInterface, RangeInterface, GraphInterface, TypeInterface, RootCodeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $inputs;
	protected $outputs;
	protected $body;
	
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
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $possibleType;
	protected $requiredType;
	protected $actualType;
	
	// code fragment
	public $code_dirty  = false;
	public $code_loaded = true;
	protected $indepDeclCode;
	protected $depDeclCode;
	protected $indepDefCode;
	protected $depDefCode;
	
	// binding fragment
	public $binding_dirty  = false;
	public $binding_loaded = true;
	
	// call fragment
	public $call_dirty  = false;
	public $call_loaded = true;
	
	// assumer fragment
	public $assumer_dirty  = false;
	public $assumer_loaded = true;
	
	
	/* GENERAL */
	public function setParent(\IdedObject $parent = null, $key = null, $fragment = null)
	{
		if ($this->parent !== null && $parent !== null) {
			throw new \RuntimeException("Setting parent to {$parent->getId()} when object already has parent {$this->parent->getId()} (".get_class($this->parent).").");
		}
		$this->parent = $parent;
		$this->parent_key = $key;
		$this->parent_fragment = $fragment;
	}
	
	public function __clone()
	{
		$this->parent = null;
		$this->parent_key = null;
		$this->parent_fragment = null;
	}
	
	public function getFragmentNames()
	{
		return array("tree","main","graph","type","code","binding","call","assumer");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "inputs", "type" => "FunctionArgumentTuple"), 
				array("name" => "outputs", "type" => "FunctionArgumentTuple"), 
				array("name" => "body", "type" => "FunctionBody"));
			case "main": return array(
				array("name" => "range", "type" => "\Source\Range"), 
				array("name" => "humanRange", "type" => "\Source\Range"), 
				array("name" => "name", "type" => "string"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
			case "code": return array(
				array("name" => "indepDeclCode", "type" => "string"), 
				array("name" => "depDeclCode", "type" => "string"), 
				array("name" => "indepDefCode", "type" => "string"), 
				array("name" => "depDefCode", "type" => "string"));
			case "binding": return array();
			case "call": return array();
			case "assumer": return array();
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "FunctionDefinition";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of FunctionDefinition as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->inputs, $x->inputs)) {
			$this->println(0, "Change detected in inputs");
			return false;
		}
		if (!$this->areEqual($this->outputs, $x->outputs)) {
			$this->println(0, "Change detected in outputs");
			return false;
		}
		if (!$this->areEqual($this->body, $x->body)) {
			$this->println(0, "Change detected in body");
			return false;
		}
	
		// main fragment
		if (!$this->main_loaded) {
			$this->loadFragment("main");
		}
		if (!$this->areEqual($this->range, $x->range)) {
			$this->println(0, "Change detected in range");
			return false;
		}
		if (!$this->areEqual($this->humanRange, $x->humanRange)) {
			$this->println(0, "Change detected in humanRange");
			return false;
		}
		if ($this->name !== $x->name) {
			$this->println(0, "Change detected in name");
			return false;
		}
	
		// graph fragment
		if (!$this->graph_loaded) {
			$this->loadFragment("graph");
		}
		if (!$this->areEqual($this->graphPrev, $x->graphPrev)) {
			$this->println(0, "Change detected in graphPrev");
			return false;
		}
	
		// type fragment
		if (!$this->type_loaded) {
			$this->loadFragment("type");
		}
		if (!$this->areEqual($this->possibleType, $x->possibleType)) {
			$this->println(0, "Change detected in possibleType");
			return false;
		}
		if (!$this->areEqual($this->requiredType, $x->requiredType)) {
			$this->println(0, "Change detected in requiredType");
			return false;
		}
		if (!$this->areEqual($this->actualType, $x->actualType)) {
			$this->println(0, "Change detected in actualType");
			return false;
		}
	
		// code fragment
		if (!$this->code_loaded) {
			$this->loadFragment("code");
		}
		if ($this->indepDeclCode !== $x->indepDeclCode) {
			$this->println(0, "Change detected in indepDeclCode");
			return false;
		}
		if ($this->depDeclCode !== $x->depDeclCode) {
			$this->println(0, "Change detected in depDeclCode");
			return false;
		}
		if ($this->indepDefCode !== $x->indepDefCode) {
			$this->println(0, "Change detected in indepDefCode");
			return false;
		}
		if ($this->depDefCode !== $x->depDefCode) {
			$this->println(0, "Change detected in depDefCode");
			return false;
		}
	
		// binding fragment
		if (!$this->binding_loaded) {
			$this->loadFragment("binding");
		}
	
		// call fragment
		if (!$this->call_loaded) {
			$this->loadFragment("call");
		}
	
		// assumer fragment
		if (!$this->assumer_loaded) {
			$this->loadFragment("assumer");
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setInputs($inputs, $notify = true)
	{
		if (!$inputs instanceof FunctionArgumentTuple && !$inputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inputs to be an instance of FunctionArgumentTuple or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->inputs, $inputs)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->inputs instanceof \RepositoryObjectParentInterface) {
				$this->inputs->setParent(null);
			}
			if ($inputs instanceof \RepositoryObjectParentInterface) {
				$inputs->setParent($this, "inputs", "tree");
			}
			$this->inputs = $inputs;
			if ($notify) {
				$this->notifyObjectDirty("inputs");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setInputsRef($inputs, \Repository $repository, $notify = true)
	{
		if (!$inputs instanceof FunctionArgumentTuple && !$inputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs inputs to be an instance of FunctionArgumentTuple or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($inputs instanceof \RepositoryObjectReference) {
			$v->set($inputs->getRefId());
		} else {
			$v->set($inputs);
		}
		$this->setInputs($v, $notify);
	}
	public function getInputs($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->inputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null inputs.");
		}
		if ($unref && $this->inputs instanceof \RepositoryObjectReference) {
			$v = $this->inputs->get();
		} else {
			$v = $this->inputs;
		}
		return $v;
	}
	
	public function setOutputs($outputs, $notify = true)
	{
		if (!$outputs instanceof FunctionArgumentTuple && !$outputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs outputs to be an instance of FunctionArgumentTuple or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->outputs, $outputs)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->outputs instanceof \RepositoryObjectParentInterface) {
				$this->outputs->setParent(null);
			}
			if ($outputs instanceof \RepositoryObjectParentInterface) {
				$outputs->setParent($this, "outputs", "tree");
			}
			$this->outputs = $outputs;
			if ($notify) {
				$this->notifyObjectDirty("outputs");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setOutputsRef($outputs, \Repository $repository, $notify = true)
	{
		if (!$outputs instanceof FunctionArgumentTuple && !$outputs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs outputs to be an instance of FunctionArgumentTuple or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($outputs instanceof \RepositoryObjectReference) {
			$v->set($outputs->getRefId());
		} else {
			$v->set($outputs);
		}
		$this->setOutputs($v, $notify);
	}
	public function getOutputs($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->outputs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null outputs.");
		}
		if ($unref && $this->outputs instanceof \RepositoryObjectReference) {
			$v = $this->outputs->get();
		} else {
			$v = $this->outputs;
		}
		return $v;
	}
	
	public function setBody($body, $notify = true)
	{
		if (!$body instanceof FunctionBody && !$body instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs body to be an instance of FunctionBody or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->body, $body)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->body instanceof \RepositoryObjectParentInterface) {
				$this->body->setParent(null);
			}
			if ($body instanceof \RepositoryObjectParentInterface) {
				$body->setParent($this, "body", "tree");
			}
			$this->body = $body;
			if ($notify) {
				$this->notifyObjectDirty("body");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setBodyRef($body, \Repository $repository, $notify = true)
	{
		if (!$body instanceof FunctionBody && !$body instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs body to be an instance of FunctionBody or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($body instanceof \RepositoryObjectReference) {
			$v->set($body->getRefId());
		} else {
			$v->set($body);
		}
		$this->setBody($v, $notify);
	}
	public function getBody($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->body === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null body.");
		}
		if ($unref && $this->body instanceof \RepositoryObjectReference) {
			$v = $this->body->get();
		} else {
			$v = $this->body;
		}
		return $v;
	}
	
	public function setRange($range, $notify = true)
	{
		if (!$range instanceof \Source\Range && !$range instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs range to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->range, $range)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->range instanceof \RepositoryObjectParentInterface) {
				$this->range->setParent(null);
			}
			if ($range instanceof \RepositoryObjectParentInterface) {
				$range->setParent($this, "range", "main");
			}
			$this->range = $range;
			if ($notify) {
				$this->notifyObjectDirty("range");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setRangeRef($range, \Repository $repository, $notify = true)
	{
		if (!$range instanceof \Source\Range && !$range instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs range to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($range instanceof \RepositoryObjectReference) {
			$v->set($range->getRefId());
		} else {
			$v->set($range);
		}
		$this->setRange($v, $notify);
	}
	public function getRange($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->range === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null range.");
		}
		if ($unref && $this->range instanceof \RepositoryObjectReference) {
			$v = $this->range->get();
		} else {
			$v = $this->range;
		}
		return $v;
	}
	
	public function setHumanRange($humanRange, $notify = true)
	{
		if (!$humanRange instanceof \Source\Range && !$humanRange instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs humanRange to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->humanRange, $humanRange)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->humanRange instanceof \RepositoryObjectParentInterface) {
				$this->humanRange->setParent(null);
			}
			if ($humanRange instanceof \RepositoryObjectParentInterface) {
				$humanRange->setParent($this, "humanRange", "main");
			}
			$this->humanRange = $humanRange;
			if ($notify) {
				$this->notifyObjectDirty("humanRange");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setHumanRangeRef($humanRange, \Repository $repository, $notify = true)
	{
		if (!$humanRange instanceof \Source\Range && !$humanRange instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs humanRange to be an instance of \Source\Range or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($humanRange instanceof \RepositoryObjectReference) {
			$v->set($humanRange->getRefId());
		} else {
			$v->set($humanRange);
		}
		$this->setHumanRange($v, $notify);
	}
	public function getHumanRange($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->humanRange === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null humanRange.");
		}
		if ($unref && $this->humanRange instanceof \RepositoryObjectReference) {
			$v = $this->humanRange->get();
		} else {
			$v = $this->humanRange;
		}
		return $v;
	}
	
	public function setName($name, $notify = true)
	{
		if (!is_string($name)) {
			throw new \InvalidArgumentException("name needs to be a string");
		}
		if ($this->name !== $name) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			$this->name = $name;
			if ($notify) {
				$this->notifyObjectDirty("name");
				$this->notifyFragmentDirty("main");
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
	
	public function setGraphPrev($graphPrev, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->graphPrev, $graphPrev)) {
			if (!$this->graph_loaded) {
				$this->loadFragment("graph");
			}
			if ($this->graphPrev instanceof \RepositoryObjectParentInterface) {
				$this->graphPrev->setParent(null);
			}
			if ($graphPrev instanceof \RepositoryObjectParentInterface) {
				$graphPrev->setParent($this, "graphPrev", "graph");
			}
			$this->graphPrev = $graphPrev;
			if ($notify) {
				$this->notifyObjectDirty("graphPrev");
				$this->notifyFragmentDirty("graph");
			}
		}
	}
	public function setGraphPrevRef($graphPrev, \Repository $repository, $notify = true)
	{
		if (!$graphPrev instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs graphPrev to be an instance of \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($graphPrev instanceof \RepositoryObjectReference) {
			$v->set($graphPrev->getRefId());
		} else {
			$v->set($graphPrev);
		}
		$this->setGraphPrev($v, $notify);
	}
	public function getGraphPrev($enforce = true, $unref = true)
	{
		if (!$this->graph_loaded) {
			$this->loadFragment('graph');
		}
		if ($enforce && $this->graphPrev === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null graphPrev.");
		}
		if ($unref && $this->graphPrev instanceof \RepositoryObjectReference) {
			$v = $this->graphPrev->get();
		} else {
			$v = $this->graphPrev;
		}
		return $v;
	}
	
	public function setPossibleType($possibleType, $notify = true)
	{
		if (!$this->areEqual($this->possibleType, $possibleType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->possibleType instanceof \RepositoryObjectParentInterface) {
				$this->possibleType->setParent(null);
			}
			if ($possibleType instanceof \RepositoryObjectParentInterface) {
				$possibleType->setParent($this, "possibleType", "type");
			}
			$this->possibleType = $possibleType;
			if ($notify) {
				$this->notifyObjectDirty("possibleType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setPossibleTypeRef($possibleType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($possibleType instanceof \RepositoryObjectReference) {
			$v->set($possibleType->getRefId());
		} else {
			$v->set($possibleType);
		}
		$this->setPossibleType($v, $notify);
	}
	public function getPossibleType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->possibleType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null possibleType.");
		}
		if ($unref && $this->possibleType instanceof \RepositoryObjectReference) {
			$v = $this->possibleType->get();
		} else {
			$v = $this->possibleType;
		}
		return $v;
	}
	
	public function setRequiredType($requiredType, $notify = true)
	{
		if (!$this->areEqual($this->requiredType, $requiredType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->requiredType instanceof \RepositoryObjectParentInterface) {
				$this->requiredType->setParent(null);
			}
			if ($requiredType instanceof \RepositoryObjectParentInterface) {
				$requiredType->setParent($this, "requiredType", "type");
			}
			$this->requiredType = $requiredType;
			if ($notify) {
				$this->notifyObjectDirty("requiredType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setRequiredTypeRef($requiredType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($requiredType instanceof \RepositoryObjectReference) {
			$v->set($requiredType->getRefId());
		} else {
			$v->set($requiredType);
		}
		$this->setRequiredType($v, $notify);
	}
	public function getRequiredType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->requiredType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null requiredType.");
		}
		if ($unref && $this->requiredType instanceof \RepositoryObjectReference) {
			$v = $this->requiredType->get();
		} else {
			$v = $this->requiredType;
		}
		return $v;
	}
	
	public function setActualType($actualType, $notify = true)
	{
		if (!$this->areEqual($this->actualType, $actualType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->actualType instanceof \RepositoryObjectParentInterface) {
				$this->actualType->setParent(null);
			}
			if ($actualType instanceof \RepositoryObjectParentInterface) {
				$actualType->setParent($this, "actualType", "type");
			}
			$this->actualType = $actualType;
			if ($notify) {
				$this->notifyObjectDirty("actualType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setActualTypeRef($actualType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($actualType instanceof \RepositoryObjectReference) {
			$v->set($actualType->getRefId());
		} else {
			$v->set($actualType);
		}
		$this->setActualType($v, $notify);
	}
	public function getActualType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->actualType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null actualType.");
		}
		if ($unref && $this->actualType instanceof \RepositoryObjectReference) {
			$v = $this->actualType->get();
		} else {
			$v = $this->actualType;
		}
		return $v;
	}
	
	public function setIndepDeclCode($indepDeclCode, $notify = true)
	{
		if (!is_string($indepDeclCode)) {
			throw new \InvalidArgumentException("indepDeclCode needs to be a string");
		}
		if ($this->indepDeclCode !== $indepDeclCode) {
			if (!$this->code_loaded) {
				$this->loadFragment("code");
			}
			$this->indepDeclCode = $indepDeclCode;
			if ($notify) {
				$this->notifyObjectDirty("indepDeclCode");
				$this->notifyFragmentDirty("code");
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
				$this->loadFragment("code");
			}
			$this->depDeclCode = $depDeclCode;
			if ($notify) {
				$this->notifyObjectDirty("depDeclCode");
				$this->notifyFragmentDirty("code");
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
				$this->loadFragment("code");
			}
			$this->indepDefCode = $indepDefCode;
			if ($notify) {
				$this->notifyObjectDirty("indepDefCode");
				$this->notifyFragmentDirty("code");
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
				$this->loadFragment("code");
			}
			$this->depDefCode = $depDefCode;
			if ($notify) {
				$this->notifyObjectDirty("depDefCode");
				$this->notifyFragmentDirty("code");
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