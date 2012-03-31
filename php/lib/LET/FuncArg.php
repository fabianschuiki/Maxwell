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
		if ($this->type()) $this->type = $this->type()->reduce();
		return $this;
	}
	
	public function buildSpecializations(array &$specializations)
	{
		parent::buildSpecializations($specializations);
		
		$type = $this->type;
		if ($type instanceof MemberConstrainedType && $type->type instanceof ConcreteType) {
			"specializing {$type->details()}\n";
			/*$spec = $this->boundTo->specialize($this->type(), $specializations);
			$this->boundTo = $spec;*/
		} 
	}
}