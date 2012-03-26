<?php
namespace LET;

abstract class Member extends Expr
{
	abstract function expr();
	abstract function name();
	
	public function details()
	{
		$expr = $this->expr();
		$str = ($expr ? $expr->details() : '?');
		return "$str.{$this->name()}";
	}
}