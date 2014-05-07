<?php
namespace Entity;

class Node
{
	protected $id;
	
	public function setID($id) { $this->id = $id; }
	public function getID() { return $this->id; }
	
	public function generateID() { if (!$this->id) $this->id = \Store\Manager::get()->getEntityStore()->allocateId(); }
}