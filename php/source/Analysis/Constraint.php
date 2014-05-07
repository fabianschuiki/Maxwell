<?php
namespace Analysis;

class Constraint
{
	static public function make()
	{
		$c = new self;
		$c->entities = func_get_args();
		return $c;
	}
	
	static public function makeWithArray($array)
	{
		$c = new self;
		$c->entities = $array;
		return $c;
	}
	
	protected $entities;
	
	public function __construct()
	{
		$this->entities = array();
	}
	
	public function getEntities() { return $this->entities; }
	public function containsEntity(\Entity\Entity $e) { return in_array($e, $this->entities, true); }
	
	public function describe()
	{
		$ids = array_map(function($e){ return $e->getID(); }, $this->entities);
		return "{".implode(",", $ids)."}";
	}
}