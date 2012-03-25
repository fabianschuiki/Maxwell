<?php
namespace AST;

class VarStmt extends Stmt
{
	public $keyword;
	public $type;
	public $name;
	
	public function __construct(\Token $keyword, IdentExpr $type, \Token $name)
	{
		$this->keyword = $keyword;
		$this->type    = $type;
		$this->name    = $name;
	}
	
	public function nice() { return "Variable Definition"; }
}