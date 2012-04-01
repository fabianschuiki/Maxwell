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
		//parent::reduce();
		if ($this->type()) $this->type = $this->type()->reduce();
		return parent::reduce();
		return $this;
	}
	
	public function buildSpecializations(array &$specializations)
	{
		parent::buildSpecializations($specializations);
		
		$type = $this->type();
		if ($type instanceof MemberConstrainedType && $type->type instanceof ConcreteType) {
			$spec = $type->type->specialize($this->type(), $specializations);
			echo "issued specialization {$this->desc()}: type now is {$spec->desc()}\n";
			$this->type = $spec;
		} 
	}
}