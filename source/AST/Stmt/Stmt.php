<?php
namespace AST\Stmt;
use AST\Node;

abstract class Stmt extends Node
{
	protected $semicolon;
	public function getSemicolon() { return $this->semicolon; }
}