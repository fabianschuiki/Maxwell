<?php
namespace AST\Stmt;

abstract class Keyword
{
	protected $keyword;
	public function getKeyword() { return $this->keyword; }
}