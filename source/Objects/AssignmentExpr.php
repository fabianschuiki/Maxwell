<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class AssignmentExpr extends Expr implements \EqualInterface, GraphInterface, TypeInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $lhs;
	protected $rhs;
	
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
		return array("tree","graph","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "lhs", "type" => "Expr"), 
				array("name" => "rhs", "type" => "Expr"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "type": return array(
				array("name" => "possibleType", "type" => ""), 
				array("name" => "requiredType", "type" => ""), 
				array("name" => "actualType", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "AssignmentExpr";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of AssignmentExpr as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->lhs, $x->lhs)) {
			$this->println(0, "Change detected in lhs");
			return false;
		}
		if (!$this->areEqual($this->rhs, $x->rhs)) {
			$this->println(0, "Change detected in rhs");
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
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setLhs($lhs, $notify = true)
	{
		if (!$lhs instanceof Expr && !$lhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs lhs to be an instance of Expr or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->lhs, $lhs)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->lhs instanceof \RepositoryObjectParentInterface) {
				$this->lhs->setParent(null);
			}
			if ($lhs instanceof \RepositoryObjectParentInterface) {
				$lhs->setParent($this, "lhs", "tree");
			}
			$this->lhs = $lhs;
			if ($notify) {
				$this->notifyObjectDirty("lhs");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setLhsRef($lhs, \Repository $repository, $notify = true)
	{
		if (!$lhs instanceof Expr && !$lhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs lhs to be an instance of Expr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($lhs instanceof \RepositoryObjectReference) {
			$v->set($lhs->getRefId());
		} else {
			$v->set($lhs);
		}
		$this->setLhs($v, $notify);
	}
	public function getLhs($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->lhs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null lhs.");
		}
		if ($unref && $this->lhs instanceof \RepositoryObjectReference) {
			$v = $this->lhs->get();
		} else {
			$v = $this->lhs;
		}
		return $v;
	}
	
	public function setRhs($rhs, $notify = true)
	{
		if (!$rhs instanceof Expr && !$rhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs rhs to be an instance of Expr or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->rhs, $rhs)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->rhs instanceof \RepositoryObjectParentInterface) {
				$this->rhs->setParent(null);
			}
			if ($rhs instanceof \RepositoryObjectParentInterface) {
				$rhs->setParent($this, "rhs", "tree");
			}
			$this->rhs = $rhs;
			if ($notify) {
				$this->notifyObjectDirty("rhs");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setRhsRef($rhs, \Repository $repository, $notify = true)
	{
		if (!$rhs instanceof Expr && !$rhs instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs rhs to be an instance of Expr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($rhs instanceof \RepositoryObjectReference) {
			$v->set($rhs->getRefId());
		} else {
			$v->set($rhs);
		}
		$this->setRhs($v, $notify);
	}
	public function getRhs($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->rhs === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null rhs.");
		}
		if ($unref && $this->rhs instanceof \RepositoryObjectReference) {
			$v = $this->rhs->get();
		} else {
			$v = $this->rhs;
		}
		return $v;
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
}