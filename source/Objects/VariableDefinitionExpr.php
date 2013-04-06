<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class VariableDefinitionExpr extends \RepositoryNodeObject implements Expr, \EqualInterface, RangeInterface, TypeInterface, ExprCodeInterface
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
	protected $possibleType;
	protected $requiredType;
	protected $actualType;
	
	// code fragment
	public $code_dirty  = false;
	public $code_loaded = true;
	protected $exprCode;
	protected $stmtsCode;
	
	
	/* GENERAL */
	public function setParent(\IdedObject $parent = null, $key = null, $fragment = null)
	{
		if ($this->parent !== null && $parent !== null) {
			throw new \RuntimeException("Setting parent to {$parent->getId()} when object already has parent {$this->parent->getId()}.");
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
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
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
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of VariableDefinitionExpr as well.');
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
		if (!$this->areEqual($this->typeExpr, $x->typeExpr)) {
			$this->println(0, "Change detected in typeExpr");
			return false;
		}
		if (!$this->areEqual($this->initialExpr, $x->initialExpr)) {
			$this->println(0, "Change detected in initialExpr");
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
		if ($this->exprCode !== $x->exprCode) {
			$this->println(0, "Change detected in exprCode");
			return false;
		}
		if ($this->stmtsCode !== $x->stmtsCode) {
			$this->println(0, "Change detected in stmtsCode");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
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
			$v = $this->range->get(!$enforce);
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
			$v = $this->humanRange->get(!$enforce);
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
	
	public function setTypeExpr($typeExpr, $notify = true)
	{
		if (!$typeExpr instanceof TypeExpr && !$typeExpr instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs typeExpr to be an instance of TypeExpr or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->typeExpr, $typeExpr)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->typeExpr instanceof \RepositoryObjectParentInterface) {
				$this->typeExpr->setParent(null);
			}
			if ($typeExpr instanceof \RepositoryObjectParentInterface) {
				$typeExpr->setParent($this, "typeExpr", "main");
			}
			$this->typeExpr = $typeExpr;
			if ($notify) {
				$this->notifyObjectDirty("typeExpr");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setTypeExprRef($typeExpr, \Repository $repository, $notify = true)
	{
		if (!$typeExpr instanceof TypeExpr && !$typeExpr instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs typeExpr to be an instance of TypeExpr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($typeExpr instanceof \RepositoryObjectReference) {
			$v->set($typeExpr->getRefId());
		} else {
			$v->set($typeExpr);
		}
		$this->setTypeExpr($v, $notify);
	}
	public function getTypeExpr($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->typeExpr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null typeExpr.");
		}
		if ($unref && $this->typeExpr instanceof \RepositoryObjectReference) {
			$v = $this->typeExpr->get(!$enforce);
		} else {
			$v = $this->typeExpr;
		}
		return $v;
	}
	
	public function setInitialExpr($initialExpr, $notify = true)
	{
		if (!$initialExpr instanceof Expr && !$initialExpr instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs initialExpr to be an instance of Expr or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->initialExpr, $initialExpr)) {
			if (!$this->main_loaded) {
				$this->loadFragment("main");
			}
			if ($this->initialExpr instanceof \RepositoryObjectParentInterface) {
				$this->initialExpr->setParent(null);
			}
			if ($initialExpr instanceof \RepositoryObjectParentInterface) {
				$initialExpr->setParent($this, "initialExpr", "main");
			}
			$this->initialExpr = $initialExpr;
			if ($notify) {
				$this->notifyObjectDirty("initialExpr");
				$this->notifyFragmentDirty("main");
			}
		}
	}
	public function setInitialExprRef($initialExpr, \Repository $repository, $notify = true)
	{
		if (!$initialExpr instanceof Expr && !$initialExpr instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs initialExpr to be an instance of Expr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($initialExpr instanceof \RepositoryObjectReference) {
			$v->set($initialExpr->getRefId());
		} else {
			$v->set($initialExpr);
		}
		$this->setInitialExpr($v, $notify);
	}
	public function getInitialExpr($enforce = true, $unref = true)
	{
		if (!$this->main_loaded) {
			$this->loadFragment('main');
		}
		if ($enforce && $this->initialExpr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null initialExpr.");
		}
		if ($unref && $this->initialExpr instanceof \RepositoryObjectReference) {
			$v = $this->initialExpr->get(!$enforce);
		} else {
			$v = $this->initialExpr;
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
			$v = $this->possibleType->get(!$enforce);
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
			$v = $this->requiredType->get(!$enforce);
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
			$v = $this->actualType->get(!$enforce);
		} else {
			$v = $this->actualType;
		}
		return $v;
	}
	
	public function setExprCode($exprCode, $notify = true)
	{
		if (!is_string($exprCode)) {
			throw new \InvalidArgumentException("exprCode needs to be a string");
		}
		if ($this->exprCode !== $exprCode) {
			if (!$this->code_loaded) {
				$this->loadFragment("code");
			}
			$this->exprCode = $exprCode;
			if ($notify) {
				$this->notifyObjectDirty("exprCode");
				$this->notifyFragmentDirty("code");
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
				$this->loadFragment("code");
			}
			$this->stmtsCode = $stmtsCode;
			if ($notify) {
				$this->notifyObjectDirty("stmtsCode");
				$this->notifyFragmentDirty("code");
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