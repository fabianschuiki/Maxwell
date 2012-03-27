<?php
namespace AST;

class VarStmt extends Stmt
{
	public $keyword;
	public $type;
	public $name;
	public $initial;
	
	public function __construct(\Token $keyword, Expr $type, \Token $name, $initial = null)
	{
		assert(!$initial || $initial instanceof Expr);
		
		$this->keyword = $keyword;
		$this->type    = $type;
		$this->name    = $name;
		$this->initial = $initial;
	}
	
	public function nice() { return "Variable definition"; }
}