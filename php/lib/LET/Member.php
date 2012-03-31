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
		parent::spawnConstraints($constraints);
		
		$expr = $this->expr();
		if ($expr) {
			if ($expr->type()) {
				$constraints[] = new MemberConstraint($expr, $this->name());
			}
			$expr->spawnConstraints($constraints);
		}
	}
	
	public function unconstrainedType()
	{
		$expr = $this->expr();
		if (!$expr) return null;
		//echo "{$this->details()} has expr {$expr->details()}\n";
		
		$type = $expr->type();
		if (!$type instanceof ConcreteType) return null;
		
		$member = null;
		foreach ($type->members() as $m) if ($m->name() == $this->name()) $member = $m;
		if (!$member instanceof TypeMember) return null;
		
		return $member->type();
	}
}