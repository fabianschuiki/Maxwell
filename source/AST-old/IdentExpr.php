<?php
namespace AST;

class IdentExpr extends Expr
{
	public $name;
	
	public function __construct(\Token $ident)
	{
		assert($ident->is('identifier'));
		$this->name = $ident;
	}
}