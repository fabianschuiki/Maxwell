<?php
namespace LET;

class ConcreteType_Spec extends ConcreteType
{
	public $original;
	public $members;
	public $specializedMembers;
	
	public function __construct(ConcreteType $original, MemberConstrainedType $type)
	{
		parent::__construct();
		
		$subscope = new Scope($original->scope, $this);
		
		$members = array();
		foreach ($original->members() as $member) $members[] = $member->cloneInto($subscope);
		
		$specializedMembers = array();
		foreach ($members as $member) {
			$name = $member->name();
			if (!isset($type->members[$name])) continue;
			$memberType = $type->members[$name];
			assert($memberType && !$memberType instanceof MemberConstrainedType);
			$member->type = Type::intersect($member->type, $memberType);
			if (!$member->type) {
				global $issues;
				$issues[] = new \Issue(
					'error',
					"Cannot specialize member '{$member->name()}' of '{$original->name()}' as type '{$memberType->details()}'.",
					$member,
					$original
				);
			}
			$specializedMembers[] = $member;
		}
		
		$this->original = $original;
		$this->members  = $members;
		$this->specializedMembers = $specializedMembers;
		$this->subscope = $subscope;
	}
	
	public function name()     { return $this->original->name(); }
	public function members()  { return $this->members; }
	public function children() { return array_merge($this->members, $this->specializedMembers); }
	
	public function details()
	{
		$members = array();
		foreach ($this->specializedMembers as $member) {
			$type = $member->type();
			$type = ($type ? $type->details() : '?');
			$members[] = "{$member->name()}:$type";
		}
		$members = implode(',', $members);
		return $this->original->details()."<".$members.">";
	}
	
	/*public function reduce()
	{
		$this->original = $this->original->reduce();
		$red = function($m){ return $m->reduce(); };
		$this->members = array_map($red, $this->members);
		$this->specializedMembers = array_map($red, $this->specializedMembers);
		return $this;
	}*/
	
	public function reduceToInterface(Scope $scope)
	{
		$cloned = clone $this;
		$cloned->original = new ConcreteType_Intf($scope, $this->original);
		$cloned->subscope = $cloned->subscope->reduceToInterface($scope);
		$cloned->members = array_map(function($m) use ($cloned) { return $m->reduceToInterface($cloned->subscope); }, $cloned->members);
		$cloned->specializedMembers = array_map(function($m) use ($cloned) { return $m->reduceToInterface($cloned->subscope); }, $cloned->specializedMembers);
		return $cloned;
	}
}