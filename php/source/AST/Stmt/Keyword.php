<?php
namespace AST\Stmt;

abstract class Keyword extends Stmt
{
	protected $keyword;
	
	public function __construct()
	{
		parent::__construct();
	}
	
	public function getKeyword() { return $this->keyword; }
}