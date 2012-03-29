<?php
namespace LET;

abstract class TypedNode extends Node
{
	public $constraints;
	public $typeConstraint;
	
	/// The node's inferred type. Consists of the unconstrained type with the type constraint applied.
	public function type() { return Type::intersect($this->unconstrainedType(), $this->typeConstraint); }
	abstract function unconstrainedType();
	
	/// Clears the constraints and the derived type constraint.
	public function clearConstraints()
	{
		foreach ($this->children() as $child) $child->clearConstraints();
		$this->constraints = array();
		$this->typeConstraint = new GenericType;
	}
	
	/// Imposes the given constraint upon the node.
	public function imposeConstraint(Constraint $constraint)
	{
		if (!$constraint->type()) {
			echo "\033[31;1mskipping constraint\033[0m {$constraint->details()} as it has no type\n";
			return;
		}
		echo "\033[1mimpose constraint\033[0m {$constraint->type()->details()} \033[1mon\033[0m {$this->details()}\n";
		
		$this->constraints[] = $constraint;
		
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
			
			$this->typeConstraint = $typeConstraint;
		}
	}
}