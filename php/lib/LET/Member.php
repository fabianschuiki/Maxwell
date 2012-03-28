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
	
	public function spawnConstraints(array &$constraints)
	{
		$expr = $this->expr();
		if ($expr) {
			if ($expr->type()) {
				$constraints[] = new MemberConstraint($expr, $this->name());
			}
			$expr->spawnConstraints($constraints);
		}
	}
}