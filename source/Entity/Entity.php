<?php
namespace Entity;

abstract class Entity extends Node
{
	/** The portion of the source file covered by this entity. */
	protected $range;
	
	/** The portion of the source file to point the programmer at in case of errors. */
	protected $humanRange;
	
	public function setRange(\Source\Range $r) { $this->range = $r; }
	public function getRange() { return $this->range; }
	
	public function setHumanRange(\Source\Range $r = null) { $this->humanRange = $r; }
	public function getHumanRange() { return $this->humanRange; }
	
	public function getHumanRangeIfPossible()
	{
		if ($this->humanRange)
			return $this->humanRange;
		return $this->range;
	}
	
	//subclass responsibilities
	public function initScope(Scope\Scope $scope = null) {}
	abstract public function getChildEntities();
	
	/** Returns a string clearly identifying this entity. Not to be shown to the end user, but
	 * rather to be used in exceptions and the like. */
	public function getInternalDescription()
	{
		$s = get_class($this)."(".$this->getId();
		if ($this->range) $s .= " ".$this->range->toString();
		$s .= ")";
		return $s;
	}
	
	/** The entity containing this entity. */
	protected $parent;
	
	/** Returns the entity's parent entity. Throws an exception if there is none. */
	public function getParent()
	{
		if (!$this->parent) {
			throw new \RuntimeException($this->getInternalDescription()." does not have a parent.");
		}
		return $this->parent;
	}
	
	/** Sets the entity's parent entity which cannot be null. */
	public function setParent(Entity $p)
	{
		$this->parent = $p;
	}
	
	/** Replaces the given child with another entity. Throws an exception if the child is not part of the entity. */
	public function replaceChild(Entity $child, Entity $with)
	{
		throw new \InvalidArgumentException($this->getInternalDescription()." does not implement replaceChild().");
	}
	
	
	public $analysis;
	public $compiler;
	
	public function __construct()
	{
		$this->analysis = \Analysis\Node\Node::makeForEntity($this);
		$this->compiler = \Compiler\Node\Node::makeForEntity($this);
	}
	
	
	/* Convenience Utilities */
	protected function makeUnknownChildException(Entity $child)
	{
		return new \InvalidArgumentException("{$this->getInternalDescription()} does not contain child {$child->getInternalDescription()}.");
	}
}