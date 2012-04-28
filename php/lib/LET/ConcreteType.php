<?php
namespace LET;

abstract class ConcreteType extends Type
{
	public $specializations;
	public $parent;
	
	abstract function name();
	abstract function members();
	
	public function __construct()
	{
		parent::__construct();
	}
	
	public $cached_isSpecific = null;
	public function isSpecific()
	{
		if ($this->cached_isSpecific !== null) return $this->cached_isSpecific;
		foreach ($this->members() as $member) {
			$type = $member->type();
			if ($type == $this) continue;
			if (!$type || !$type->isSpecific()) {
				return false;
				$this->cached_isSpecific = false;
			}
		}
		$this->cached_isSpecific = true;
		return true;
	}
	
	public function desc()
	{
		$str = parent::desc();
		if ($this->parent) $str .= " : {$this->parent->details()}";
		return $str;
	}
	
	public function details()
	{
		return "{$this->name()}";
	}
	
	public function children()
	{
		$c = $this->members();
		if ($this->parent) $c[] = $this->parent;
		return $c;
	}
	
	public function type()   { return $this; }
	public function parent() { return $this->parent; }
	
	public function specialize(MemberConstrainedType $type, array &$specializations)
	{
		if (Type::intersect($this, $type, $this->scope) === $this) return $this;
		if ($this->specializations) {
			//echo "looking for existing specializations...\n";
			foreach ($this->specializations as $spec) {
				$inter = Type::intersect($spec, $type);
				//$details = ($inter ? $inter->details() : 'null');
				//echo "- intersected {$spec->details()} and {$type->details()}  ->  {$details}\n";
				if ($inter) return $spec;
			}
		} else {
			$this->specializations = array();
		}
		
		echo "\033[1mspecializing\033[0m {$this->desc()} for {$type->details()}\n";
		
		foreach ($type->members as $name => $memberType) {
			if (!$memberType instanceof MemberConstrainedType) continue;
			$type->members[$name] = $memberType->type->specialize($memberType, $specializations);
		}
		
		$spec = new ConcreteType_Spec($this, $type);
		$this->specializations[] = $spec;
		$specializations[] = $spec;
		$this->scope->add($spec);
		return $spec;
	}
	
	public function reduceToInterface(Scope $scope)
	{
		return new ConcreteType_Intf($scope, $this);
	}
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new ConcreteType_Proxy($this->id);
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		if ($this->scope->rootNode() === $root) return parent::unbindFromInterfaces($root);
		//$root->externalNodes[] = $this->id;
		return new ConcreteType_Proxy($this->id);
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		$ids[] = $this->id;
		parent::gatherExternalNodeIDs($ids);
	}
	
	public function reduce()
	{
		if ($this->parent) $this->parent = $this->parent->reduce();
		return parent::reduce();
	}
}