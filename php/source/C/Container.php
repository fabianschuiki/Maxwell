<?php
namespace C;

class Container extends Node
{
	public $nodes;
	
	public function __construct()
	{
		$this->nodes = array();
	}
	
	public function add(\C\Node $node)
	{
		$this->nodes[] = $node;
	}
}