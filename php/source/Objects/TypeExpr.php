<?php
/* Copyright © 2013 Fabian Schuiki.
 * Automatically generated entity. */
namespace Objects;

class TypeExpr extends \RepositoryNodeObject implements \EqualInterface, GraphInterface
{
	/* PROPERTIES */
	protected $parent = null;
	protected $parent_key = null;
	protected $parent_fragment = null;
	
	// tree fragment
	public $tree_dirty  = false;
	public $tree_loaded = true;
	protected $expr;
	
	// graph fragment
	public $graph_dirty  = false;
	public $graph_loaded = true;
	protected $graphPrev;
	
	// type fragment
	public $type_dirty  = false;
	public $type_loaded = true;
	protected $evaluatedType;
	
	
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
		return array("tree","graph","type");
	}
	
	public function getFragment($name)
	{
		switch ($name) {
			case "tree": return array(
				array("name" => "expr", "type" => "Expr"));
			case "graph": return array(
				array("name" => "graphPrev", "type" => "\RepositoryObjectReference"));
			case "type": return array(
				array("name" => "evaluatedType", "type" => ""));
		}
		throw new \RuntimeException("Fragment $name does not exist.");
	}
	
	public function getClass()
	{
		return "TypeExpr";
	}
	
	public function isEqualTo($x)
	{
		if (!$x instanceof self) {
			throw new \InvalidArgumentException('x needs to be an instance of TypeExpr as well.');
		}
		// tree fragment
		if (!$this->tree_loaded) {
			$this->loadFragment("tree");
		}
		if (!$this->areEqual($this->expr, $x->expr)) {
			$this->println(0, "Change detected in expr");
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
		if (!$this->areEqual($this->evaluatedType, $x->evaluatedType)) {
			$this->println(0, "Change detected in evaluatedType");
			return false;
		}
	
		return true;
	}
	
	
	/* ACCESSORS */
	public function setExpr($expr, $notify = true)
	{
		if (!$expr instanceof Expr && !$expr instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs expr to be an instance of Expr or \RepositoryObjectReference');
		}
		if (!$this->areEqual($this->expr, $expr)) {
			if (!$this->tree_loaded) {
				$this->loadFragment("tree");
			}
			if ($this->expr instanceof \RepositoryObjectParentInterface) {
				$this->expr->setParent(null);
			}
			if ($expr instanceof \RepositoryObjectParentInterface) {
				$expr->setParent($this, "expr", "tree");
			}
			$this->expr = $expr;
			if ($notify) {
				$this->notifyObjectDirty("expr");
				$this->notifyFragmentDirty("tree");
			}
		}
	}
	public function setExprRef($expr, \Repository $repository, $notify = true)
	{
		if (!$expr instanceof Expr && !$expr instanceof \RepositoryObjectReference) {
			throw new \InvalidArgumentException('Object '.$this->getId().' needs expr to be an instance of Expr or \RepositoryObjectReference');
		}
		$v = new \RepositoryObjectReference($repository);
		if ($expr instanceof \RepositoryObjectReference) {
			$v->set($expr->getRefId());
		} else {
			$v->set($expr);
		}
		$this->setExpr($v, $notify);
	}
	public function getExpr($enforce = true, $unref = true)
	{
		if (!$this->tree_loaded) {
			$this->loadFragment('tree');
		}
		if ($enforce && $this->expr === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null expr.");
		}
		if ($unref && $this->expr instanceof \RepositoryObjectReference) {
			$v = $this->expr->get();
		} else {
			$v = $this->expr;
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
	
	public function setEvaluatedType($evaluatedType, $notify = true)
	{
		if (!$this->areEqual($this->evaluatedType, $evaluatedType)) {
			if (!$this->type_loaded) {
				$this->loadFragment("type");
			}
			if ($this->evaluatedType instanceof \RepositoryObjectParentInterface) {
				$this->evaluatedType->setParent(null);
			}
			if ($evaluatedType instanceof \RepositoryObjectParentInterface) {
				$evaluatedType->setParent($this, "evaluatedType", "type");
			}
			$this->evaluatedType = $evaluatedType;
			if ($notify) {
				$this->notifyObjectDirty("evaluatedType");
				$this->notifyFragmentDirty("type");
			}
		}
	}
	public function setEvaluatedTypeRef($evaluatedType, \Repository $repository, $notify = true)
	{
		$v = new \RepositoryObjectReference($repository);
		if ($evaluatedType instanceof \RepositoryObjectReference) {
			$v->set($evaluatedType->getRefId());
		} else {
			$v->set($evaluatedType);
		}
		$this->setEvaluatedType($v, $notify);
	}
	public function getEvaluatedType($enforce = true, $unref = true)
	{
		if (!$this->type_loaded) {
			$this->loadFragment('type');
		}
		if ($enforce && $this->evaluatedType === null) {
			throw new \RuntimeException("Object {$this->getId()} expected to have non-null evaluatedType.");
		}
		if ($unref && $this->evaluatedType instanceof \RepositoryObjectReference) {
			$v = $this->evaluatedType->get();
		} else {
			$v = $this->evaluatedType;
		}
		return $v;
	}
}