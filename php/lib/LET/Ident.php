<?php
namespace LET;

abstract class Ident extends Expr
{
	abstract function name();
	
	public function details()
	{
		return $this->name();
	}
}