<?php
namespace AST;

class MemberExpr extends Expr
{
	public $expr;
	public $name;
	
	public function __construct(Expr $expr, \Token $name)
	{
		assert($name->is('identifier'));
		
		$this->expr = $expr;
		$this->name = $name;
	}
}