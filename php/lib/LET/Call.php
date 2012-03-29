<?php
namespace LET;

abstract class Call extends Expr
{
	abstract function callee();
	abstract function args();
	
	public function details()
	{
		$callee = $this->callee();
		$callee = ($callee ? $callee->details() : '?');
		
		$args = array_map(function($arg){
			return ($arg ? $arg->details() : '?');
		}, $this->args());
		$args = implode(", ", $args);
		
		return "'$callee' ($args)";
	}
	
	public function children()
	{
		return array_merge(array($this->callee()), $this->args());
	}
	
	public function type()
	{
		$type = null;
		$callee = $this->callee();
		if ($callee) {
			$func = $callee->type();
			if ($func instanceof FuncType) $type = $func->out();
		}
		
		return Type::Intersect($type, $this->typeConstraint);
	}
	
	public function imposeConstraint(Constraint $constraint)
	{
		parent::imposeConstraint($constraint);
		
		$callee = $this->callee();
		if ($callee) $callee->typeConstraint = new FuncType($this->scope, new GenericType, $constraint->type());
		/*$type = $this->typeConstraint;
		if (!$type instanceof TypeTuple) return;
		
		foreach ($this->exprs as $name => $expr) {
			$constrained = null;
			if (isset($type->fields[$name])) $constrained = $type->fields[$name];
			$expr->typeConstraint = $constrained;
		}*/
	}
}