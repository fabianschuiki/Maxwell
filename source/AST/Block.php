<?php
namespace AST;
use Lexer\TokenGroup;

class Block extends Node
{
	protected $group;
	protected $stmts;
	
	public function __construct(array $stmts, TokenGroup $group = null)
	{
		foreach ($stmts as $s) assert($s instanceof Stmt\Stmt);
		$this->group = $group;
		$this->stmts = $stmts;
	}
	
	public function getGroup() { return $this->group; }
	public function getStmts() { return $this->stmts; }
}