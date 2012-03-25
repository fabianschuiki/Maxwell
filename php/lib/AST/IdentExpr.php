<?php
namespace AST;

class IdentExpr extends Expr
{
	public $ident;
	
	public function __construct(\Token $ident)
	{
		assert($ident->is('identifier'));
		$this->ident = $ident;
	}
}