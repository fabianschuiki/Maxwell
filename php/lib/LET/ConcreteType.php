<?php
namespace LET;

abstract class ConcreteType extends Type
{
	public $specializations;
	
	abstract function name();
	abstract function members();
	
	public function isSpecific()
	{
		foreach ($this->members() as $member) {
			$type = $member->type();
			if ($type == $this) continue;
			if (!$type || !$type->isSpecific()) return false;
		}
		return true;
	}
	
	public function details()
	{
		return "{$this->name()}";
	}
	
	public function children()
	{
		return $this->members();
	}
	
	public function type() { return $this; }
	
	public function specialize(MemberConstrainedType $type, array &$specializations)
	{
		if (Type::intersect($this, $type) === $this) return $this;
		if ($this->specializations) {
			foreach ($this->specializations as $spec) if (Type::intersect($spec, $type)) return $spec;
		} else {
			$this->specializations = array();
		}
		
		echo "\033[1mspecializing\033[0m {$this->details()} for {$type->details()}\n";
		
		foreach ($type->members as $name => $memberType) {
			if (!$memberType instanceof MemberConstrainedType) continue;
			echo "subspecialization {$memberType->details()}\n";
			$type->members[$name] = $memberType->type->specialize($memberType, $specializations);
			echo "-> yields {$type->members[$name]->details()}\n";
		}
		
		$spec = new ConcreteType_Spec($this, $type);
		$this->specializations[] = $spec;
		$specializations[] = $spec;
		$this->scope->add($spec);
		return $spec;
	}
}