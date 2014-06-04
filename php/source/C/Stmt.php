<?php
namespace C;

class Stmt extends Node
{
	public $code;
	
	public function __construct($code = null)
	{
		parent::__construct();
		$this->code = $code;
	}
	
	public function getStmt()
	{
		return $this->code.";";
	}
}