<?php
namespace AST\Stmt;

abstract class Keyword extends Stmt
{
	protected $keyword;
	public function getKeyword() { return $this->keyword; }
}