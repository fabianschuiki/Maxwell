<?php
namespace LET;

class ConcreteType_Spec extends ConcreteType
{
	public $original;
	public $members;
	
	public function __construct(ConcreteType $original, MemberConstrainedType $type)
	{
		$subscope = new Scope($original->scope, $this);
		
		$members = array();
		foreach ($original->members() as $member) $members[] = $member->cloneInto($subscope);
		
		foreach ($members as $member) {
			$name = $member->name();
			if (!isset($type->members[$name])) continue;
			$memberType = $type->members[$name];
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
		}
		
		$this->original = $original;
		$this->members  = $members;
		$this->subscope = $subscope;
	}
	
	public function name()    { return $this->original->name(); }
	public function members() { return $this->members; }
	
	public function details()
	{
		$members = array();
		foreach ($this->members as $member) {
			$type = $member->type();
			$type = ($type ? $type->details() : '?');
			$members[] = "$type {$member->name()}";
		}
		$members = implode(', ', $members);
		return parent::details()."<".$members.">";
	}
}