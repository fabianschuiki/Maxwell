<?php
namespace AST\Stmt;
use AST\Node;

abstract class Stmt extends Node
{
	protected $semicolon;
	
	public function __construct()
	{
		parent::__construct();
	}
	
	public function getSemicolon() { return $this->semicolon; }
}