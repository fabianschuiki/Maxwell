<?php
namespace AST;

class TypeStmt extends Stmt
{
	public $name;
	public $stmts;
	
	public function __construct(\Token $name, array $stmts)
	{
		assert($name->is('identifier'));
		$this->name  = $name;
		$this->stmts = $stmts;
	}
}