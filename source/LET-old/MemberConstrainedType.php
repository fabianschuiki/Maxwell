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
	
	public function isSpecific() { return $this->type->isSpecific(); }
	public function children() { return array_merge(array($this->type), $this->members); }
	
	public function reduce()
	{
		$this->type = $this->type->reduce();
		$this->members = array_map(function($m){ return $m->reduce(); }, $this->members);
		//echo "reducing {$this->desc()} to {$this->type->desc()}\n";
		if ($this->type instanceof ConcreteType && $this->type->isSpecific()) return $this->type;
		if ($this->type instanceof ConcreteType) {
			/*$members = $this->members;
			foreach ($this->type->members as $member) {
				$name = $member->name();
				if (!isset($members[$name])) continue;
				//if (!Type::intersect($member->type(), $members[$name])) {
				if ($member->type() != $members[$name]) {
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
			echo "reducing {$this->desc()} to {$this->type->desc()}\n";
			return $this->type;*/
		}
		return $this;
	}
	
	public function reduceToAbsolute(Scope $scope)
	{
		$type    = $this->type->reduceToAbsolute($scope);
		$members = array_map(function($m) use ($scope) { return $m->reduceToAbsolute($scope); }, $this->members);
		return new self($type, $members, array());
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		if ($this->type) $this->type = $this->type->unbindFromInterfaces($root);
		$this->members = array_map(function($m) use ($root) { return $m->unbindFromInterfaces($root); }, $this->members);
		return parent::unbindFromInterfaces($root);
	}
}