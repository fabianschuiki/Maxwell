<?php
namespace LET;

class Proxy extends Node
{
	public $id;
	
	public function __construct($id)
	{
		assert(is_string($id) || is_numeric($id));
		$this->id = $id;
	}
	
	public function details() { return "#{$this->id}"; }
}