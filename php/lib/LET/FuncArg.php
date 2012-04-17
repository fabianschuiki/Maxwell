<?php
namespace LET;

abstract class FuncArg extends TypedNode
{
	public $type;
	
	abstract function name();
	
	public function details()
	{
		$type = $this->type();
		$type = ($type ? $type->details() : '?');
		
		return "$type {$this->name()}";
	}
	public function unconstrainedType() { return $this->type; }
	
	public function reduce()
	{
		if ($this->type()) {
			$this->type = $this->type()->reduce();
			$this->parent->maybeTypeChanged();
		}
		return parent::reduce();
	}
	
	public function buildSpecializations(array &$specializations)
	{
		parent::buildSpecializations($specializations);
		
		$type = $this->type();
		if ($type instanceof MemberConstrainedType && $type->type instanceof ConcreteType) {
			$spec = $type->type->specialize($this->type(), $specializations);
			//echo "issued specialization {$this->desc()}: type now is {$spec->desc()}\n";
			$this->type = $spec;
			$this->parent->maybeTypeChanged();
		} 
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		parent::imposeTypeConstraint($type);
		$this->parent->maybeTypeChanged();
	}
	
	public function reduceToInterface(Scope $scope)
	{
		return new FuncArg_Intf($scope, $this);
	}
}