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
	
	public function setHumanRange(\Source\Range $r) { $this->humanRange = $r; }
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
		$s = get_class($this);
		if ($this->range) $s .= " ".$this->range->toString();
		return $s;
	}
	
	/** The entity containing this entity. */
	protected $parent;
	
	public function getParent()
	{
		if (!$this->parent) {
			throw new \RuntimeException($this->getInternalDescription()." does not have a parent.");
		}
		return $this->parent;
	}
	
	public function setParent(Entity $p)
	{
		$this->parent = $p;
	}
	
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
}