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
		if (!$member) return /*new GenericType*/null;
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
		
		/*$exprType = $expr->type();
		if (!$exprType) $exprType = new GenericType;*/
		
		$constraint = new MemberConstrainedType(new GenericType, array(strval($this->name()) => $type), array(strval($this->name()) => $this));
		
		if ($expr->typeConstraint && !Type::intersect($expr->typeConstraint, $constraint)) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Member '{$this->name()}' is not of type '{$type->details()}'.",
				$this
			);
			return;
		}
		
		$expr->imposeTypeConstraint($constraint);
		$tp = $expr->type();
		$tp = ($tp ? $tp->details() : '?');
		//echo "constrained {$expr->desc()} to {$constraint->details()}, yielding $tp\n";
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
	
	public function bind()
	{
		parent::bind();
		
		if (!$this->typeMember()) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"{$this->expr()->type()->name()} has no member named '{$this->name()}'.",
				$this
			);
		}
	}
}