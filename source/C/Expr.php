<?php
namespace C;

class Expr extends Node
{
	public $code;
	
	public function __construct($code = null)
	{
		$this->code = $code;
	}
	
	public function getExpr() { return $this->code; }
	public function getStmt() { return $this->getExpr().";"; }
}