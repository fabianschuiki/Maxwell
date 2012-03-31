<?php
namespace LET;

abstract class TypedNode extends Node
{
	public $constraints;
	public $typeConstraint;
	
	public function __construct()
	{
		$this->constraints = array();
		$this->typeConstraint = new GenericType;
	}
	
	/// The node's inferred type. Consists of the unconstrained type with the type constraint applied.
	public function type()
	{
		if (!$this->unconstrainedType() || !$this->typeConstraint) return $null;
		$type = Type::intersect($this->unconstrainedType(), $this->typeConstraint);
		if ($type && !$type instanceof ConcreteType) $type = $type->reduce();
		return $type;
	}
	abstract function unconstrainedType();
	
	/// Clears the constraints and the derived type constraint.
	public function clearConstraints()
	{
		foreach ($this->children() as $child) $child->clearConstraints();
		$this->constraints = array();
		$this->typeConstraint = new GenericType;
	}
	
	/// Imposes the given constraint upon the node. Generates further imposeTypeConstraint calls.
	public function imposeConstraint(Constraint $constraint)
	{
		if (!$constraint->type()) {
			echo "\033[31;1mskipping constraint\033[0m {$constraint->details()} as it has no type\n";
			return;
		}
		echo "\033[1mimpose constraint\033[0m {$constraint->type()->details()} \033[1mon\033[0m {$this->desc()}\n";
		
		$this->constraints[] = $constraint;
		
		//TODO: most of this code could be obsolete. Maybe we should just call imposeTypeConstraint.
		$typeConstraint = $this->typeConstraint;
		if ($typeConstraint) {
			$typeConstraint = Type::intersect($typeConstraint, $constraint->type());
			
			global $issues;
			if (!$typeConstraint) {
				$issues[] = new \Issue(
					'error',
					"Constraint {$constraint->details()} conflicts with other constraints.",
					$this
				);
			} else if (!$typeConstraint || !Type::intersect($typeConstraint, $this->type())) {
				$type = $this->type();
				$type = ($type ? $type->details() : '?');
				$issues[] = new \Issue(
					'error',
					"Entity of type '$type' cannot meet constraint {$constraint->details()}.",
					$this
				);
			}
			
			$this->imposeTypeConstraint($constraint->type());
		}
	}
	
	/// Imposes the given type constraint upon the node.
	public function imposeTypeConstraint(Type $type)
	{
		$constraint = null;
		if ($this->typeConstraint) $constraint = Type::intersect($this->typeConstraint, $type);
		if (!$constraint) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Unable to constrain to '{$type->details()}'.",
				$this
			);
		}
		$this->typeConstraint = $constraint;
	}
	
	public function reduce()
	{
		//$red = $this->typeConstraint->reduce();
		//echo "reducing {$this->desc()} with constraint {$this->typeConstraint->details()} to {$red->details()}\n";
		if ($this->typeConstraint) $this->typeConstraint = $this->typeConstraint->reduce();
		return parent::reduce();
	}
}