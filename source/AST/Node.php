<?php
namespace AST;

abstract class Node
{
	protected $id;
	
	public function __construct()
	{
		$this->id = \IDProvider::makeID();
	}
	
	public function getID() { return $this->id; }
}