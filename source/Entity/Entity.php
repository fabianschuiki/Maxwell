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
	public function initScope(Scope\Scope $scope) {}
	abstract public function getChildEntities();
}