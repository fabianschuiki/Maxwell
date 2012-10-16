<?php
namespace AST;
use Lexer\TokenGroup;

class Block extends Node
{
	protected $group;
	protected $stmts;
	protected $range;
	
	public function __construct(array $stmts, TokenGroup $group = null)
	{
		parent::__construct();
		foreach ($stmts as $s) assert($s instanceof Stmt\Stmt);
		$this->group = $group;
		$this->stmts = $stmts;
		if ($group) {
			$this->range = $group->getRange();
		} else if (count($stmts)) {
			$this->range = \Source\Range::union(array_map(function($s){ return $s->getRange(); }, $stmts));
		}
	}
	
	public function getGroup() { return $this->group; }
	public function getStmts() { return $this->stmts; }
	
	public function getRange() { return $this->range; }
}