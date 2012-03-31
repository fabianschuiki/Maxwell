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
	
	public function children() { return array($this->expr()); }
	
	public function unconstrainedType()
	{
		$member = $this->typeMember();
		if (!$member) return null;
		return $member->type();
	}
	
	public function typeMember()
	{
		$expr = $this->expr();
		if (!$expr) return null;
		
		$type = $expr->type();
		if (!$type instanceof ConcreteType) return null;
		
		foreach ($type->members() as $member) if ($member->name() == $this->name()) return $member;
		return null;
	}
	
	private function imposeMemberConstraintOnExpr()
	{
		$expr = $this->expr();
		$type = $this->type();
		if (!$expr || !$type) return;
		
		$constraint = new MemberConstrainedType(new GenericType, array($this->name() => $type), array($this->name() => $this));
		$expr->imposeTypeConstraint($constraint);
		$tp = $expr->type();
		$tp = ($tp ? $tp->details() : $tp);
		echo "constrained {$expr->desc()} to {$constraint->details()}, yielding $tp\n";
	}
	
	public function clearConstraints()
	{
		parent::clearConstraints();
		$this->imposeMemberConstraintOnExpr();
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		parent::imposeTypeConstraint($type);
		$this->imposeMemberConstraintOnExpr();
	}
}