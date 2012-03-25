<?php
namespace AST;

class TypeStmt extends Stmt
{
	public $keyword;
	public $name;
	public $stmts;
	
	public function __construct(\Token $keyword, \Token $name, array $stmts)
	{
		assert($keyword->is('keyword'));
		assert($name->is('identifier'));
		$this->keyword = $keyword;
		$this->name    = $name;
		$this->stmts   = $stmts;
	}
	
	public function nice() { return "Type Definition"; }
}