<?php
namespace AST;

class VarExpr extends Expr
{
	public $type;
	public $name;
	
	public function __construct(IdentExpr $type, \Token $name)
	{
		$this->type = $type;
		$this->name = $name;
	}
	
	public function nice() { return "Variable Definition"; }
}