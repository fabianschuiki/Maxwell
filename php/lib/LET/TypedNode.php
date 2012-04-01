<?php
namespace LET;

abstract class TypedNode extends Node
{
	public $constraints;
	public $typeConstraint;
	public $lastConfirmedType;
	
	public function __construct()
	{
		$this->constraints = array();
		$this->typeConstraint = new GenericType;
	}
	
	/// The node's inferred type. Consists of the unconstrained type with the type constraint applied.
	public function type()
	{
		if (!$this->unconstrainedType() || !$this->typeConstraint) return $null;
		$type = Type::intersectTwo($this->unconstrainedType(), $this->typeConstraint, $this->scope);
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
		$this->maybeTypeChanged();
	}
	
	/// Imposes the given constraint upon the node. Generates further imposeTypeConstraint calls.
	public function imposeConstraint(Constraint $constraint)
	{
		if (!$constraint->type()) {
			echo "\033[31;1mskipping constraint\033[0m {$constraint->details()} as it has no type\n";
			return;
		}
		
		if (!in_array($constraint, $this->constraints, true)) $this->constraints[] = $constraint;
		
		//TODO: most of this code could be obsolete. Maybe we should just call imposeTypeConstraint.
		$typeConstraint = $this->typeConstraint;
		if ($typeConstraint) {
			$typeConstraint = Type::intersectTwo($typeConstraint, $constraint->type(), $this->scope);
			if ($typeConstraint == $this->typeConstraint) /*echo " - superfluous constraint {$constraint->details()}\n"*/return;
			
			global $issues;
			if (!$typeConstraint) {
				$issues[] = new \Issue(
					'error',
					"Constraint {$constraint->details()} conflicts with other constraints.",
					$this
				);
			} else if (!$typeConstraint || !Type::intersectTwo($typeConstraint, $this->type())) {
				$type = $this->type();
				$type = ($type ? $type->details() : '?');
				$issues[] = new \Issue(
					'error',
					"Entity of type '$type' cannot meet constraint {$constraint->details()}.",
					$this
				);
			}
			
			$constraint->isImposing = true;
			$this->imposeTypeConstraint($constraint->type());
			$constraint->isImposing = false;
		}
	}
	
	/// Imposes the given type constraint upon the node.
	public function imposeTypeConstraint(Type $type)
	{
		$constraint = null;
		if ($this->typeConstraint) $constraint = Type::intersectTwo($this->typeConstraint, $type, $this->scope);
		if (!$constraint) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Unable to constrain to '{$type->details()}'.",
				$this
			);
		}
		//echo "\033[1mimpose\033[0m {$constraint->details()} \033[1mon\033[0m {$this->desc()}\n";
		$this->typeConstraint = $constraint;
		$this->maybeTypeChanged();
	}
	
	public function maybeTypeChanged()
	{
		$type = $this->type();
		if ($type != $this->lastConfirmedType && $this->lastConfirmedType) {
			//echo " - type changed {$this->desc()} from {$this->lastConfirmedType->details()}\n";
			$this->lastConfirmedType = $type;
			//echo "\033[32;1mtype changed\033[0m: {$this->desc()}".($this->parent ? ' -> propagates to parent' : '')."\n";
			$this->notifyTypeChanged();
			$this->propagateTypeChange();
		}
		$this->lastConfirmedType = $type;
	}
	
	public function notifyTypeChanged()
	{
		if ($this->parent) {
			//echo "\033[32mstarting notification chain\033[0m for {$this->desc()} at {$this->parent->desc()}\n";
			$this->parent->notifyNodeChangedType($this);
		}
	}
	
	public function notifyNodeChangedType(Node $node)
	{
		//echo "\033[0mnotify\033[0m: {$this->desc()}\n";
		if ($node === $this) {
			//echo " -> \033[31mterminating notification chain\033[0m\n";
			return;
		}
		parent::notifyNodeChangedType($node);
	}
	
	public function propagateTypeChange()
	{
		foreach ($this->constraints as $constraint) {
			if (!$constraint instanceof EqualTypeConstraint/* || $constraint->isImposing*/) continue;
			//echo " - re-impose {$constraint->details()}\n";
			$constraint->impose();
			//$constraint->imposeAgain = true;
		}
		//if ($this->parent) $this->parent->notifyNodeChangedType($this);
	}
	
	public function reduce()
	{
		//$red = $this->typeConstraint->reduce();
		//echo "reducing {$this->desc()} with constraint {$this->typeConstraint->details()} to {$red->details()}\n";
		if ($this->typeConstraint) $this->typeConstraint = $this->typeConstraint->reduce();
		return parent::reduce();
	}
	
	public function complainAboutAmbiguities()
	{
		//echo " - complaint opportunity for {$this->desc()}\n";
		global $issues;
		$type = $this->type();
		if (!$type) {
			$issues[] = new \Issue(
				'error',
				"Impossible to infer type of {$this->nice()}.",
				$this
			);
		} else if (!$type->isSpecific()) {
			$issues[] = new \Issue(
				'error',
				"{$this->nice()} is of generic type '{$this->niceType()}' which cannot be compiled.",
				$this
			);
		} else {
			parent::complainAboutAmbiguities();
		}
	}
	
	public function niceType() { return $this->type()->details(); }
}