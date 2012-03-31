<?php
namespace LET;

class MemberConstrainedType extends Type
{
	public $type;
	public $members;
	public $issuingNodes;
	
	public function __construct(Type $type, array $members, array $issuingNodes)
	{
		$this->type         = $type;
		$this->members      = $members;
		$this->issuingNodes = $issuingNodes;
	}
	
	public function details()
	{
		$types = array();
		foreach ($this->members as $member => $type) {
			$str = $member;
			if ($type && !$type instanceof GenericType) $str .= ":{$type->details()}";
			$types[] = $str;
		}
		
		return "{$this->type->details()}[".implode(',', $types)."]";
	}
	
	public function isSpecific()
	{
		return $this->type->isSpecific();
	}
	
	public function reduce()
	{
		if ($this->type) $this->type = $this->type->reduce();
		if ($this->type instanceof ConcreteType) {
			$members = $this->members;
			foreach ($this->type->members as $member) {
				$name = $member->name();
				if (!isset($members[$name])) continue;
				if (!Type::intersect($member->type(), $members[$name])) {
					global $issues;
					$issues[] = new \Issue(
						'error',
						"Member '$name' of type '{$this->type->name()}' is not of type {$members[$name]->type()->details()}.",
						$this->issuingNodes[$name]
					);
					return null;
				}
				unset($members[$name]);
			}
			foreach ($members as $name => $member) {
				global $issues;
				$issues[] = new \Issue(
					'error',
					"Type '{$this->type->name()}' has no member named '$name'.",
					$this->type,
					$this->issuingNodes[$name]
				);
			}
			if (count($members)) return null;
			return $this->type;
		}
		return $this;
	}
}