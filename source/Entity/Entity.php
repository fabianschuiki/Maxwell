<?php
namespace Entity;

class Entity
{
	protected $id;
	
	/** The portion of the source file covered by this entity. */
	protected $range;
	
	/** The portion of the source file to point the programmer at in case of errors. */
	protected $humanRange;
	
	
	public function setID($id) { $this->id = $id; }
	public function getID() { return $this->id; }
	
	public function generateID() { if (!$this->id) $this->id = \Store\Manager::get()->getEntityStore()->allocateId(); }
	
	public function setRange(\Source\Range $r) { $this->range = $r; }
	public function getRange() { return $this->range; }
	
	public function setHumanRange(\Source\Range $r) { $this->humanRange = $r; }
	public function getHumanRange() { return $this->humanRange; }
}