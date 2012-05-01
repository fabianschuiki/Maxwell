<?php
namespace LET;

abstract class TypeMember extends TypedNode
{
	public $type;
	
	abstract function name();
	public function unconstrainedType() { return $this->type; }
	
	public function details()
	{
		$type = ($this->type ? $this->type->details() : '?');
		return "$type {$this->name()}";
	}
	
	public function children()
	{
		$type = $this->type;
		if (!$type || ($type instanceof ConcreteType && !$type instanceof ConcreteType_Proxy)) return array();
		return array($type);
	}
	
	public function reduce()
	{
		$type = $this->type;
		if ($type && (!$type instanceof ConcreteType || $type instanceof ConcreteType_Proxy)) $this->type = $type->reduce();
		return $this;
	}
	
	public function reduceToInterface(Scope $scope)
	{
		return new TypeMember_Intf($scope, $this);
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		if ($this->type) $this->type->gatherExternalNodeIDs($ids);
		parent::gatherExternalNodeIDs($ids);
	}
}