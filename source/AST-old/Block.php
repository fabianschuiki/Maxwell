<?php
namespace AST;

class Block extends Node
{
	public $group;
	public $stmts;
	
	public function __construct($group, $stmts)
	{
		assert(!$group || $group instanceof \TokenGroup);
		assert(is_array($stmts) || $stmts instanceof Stmt);
		 
		$this->group = $group;
		$this->stmts = (is_array($stmts) ? $stmts : array($stmts));
	}
}
