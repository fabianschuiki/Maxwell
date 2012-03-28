<?php
namespace LET;

class MemberConstraint extends Constraint
{
	public $node;
	public $members;
	public $type;
	
	public function __construct(Node $node, $members)
	{
		if (!is_array($members)) $members = array_slice(func_get_args(), 1);
		
		$node = $node->constraintTarget();
		assert($node->type() instanceof Type);
		
		$this->node    = $node;
		$this->members = $members;
	}
	
	public function details()
	{
		return "({$this->node->details()}).{".implode(', ', $this->members).'}';
	}
	
	///Returns whether the constraint is met.
	public function met()
	{
		/*$nodes = $this->nodes;
		while (count($nodes) > 0) {
			$a = array_shift($nodes);
			foreach ($nodes as $b) {
				if ($a->type() != $b->type()) return false;
			}
		}
		return true;*/
		return false;
	}
	
	public function type() { return $this->type; }
	
	///Merges the other constraint if they share at least one node. Returns true if a merge occured, false otherwise.
	public function merge(MemberConstraint $other)
	{
		if ($this->node !== $other->node) return false;
		
		$this->members = array_unique(array_merge($this->members, $other->members));
		return true;
	}
	
	public function impose()
	{
		$types = array();
		$scope = $this->node->scope;
		while ($scope) {
			foreach ($scope->types as $type) {
				$members = array_map(function($member){ return $member->name(); }, $type->members());
				$missing = array_diff($this->members, $members);
				if (!count($missing)) $types[] = $type;
			}
			$scope = $scope->outer;
		}
		
		$type = null;
		if (count($types) == 0) {
			$members = implode(', ', $this->members);
			global $issues;
			$issues[] = new \Issue(
				'error',
				"There is no type with members $members.",
				$this->node->range()
			);
		}
		if (count($types) == 1) $type = $types[0];
		if (count($types) > 1)  $type = new TypeSet($this->node->scope, $types);
		$this->type = $type;
		//if (!$type) return;
		
		$this->node->imposeConstraint($this);
		
		//if ($type) 
		
		/*$types = array_map(function($node){ return $node->type(); }, $this->nodes);
		if (in_array(null, $types, true)) return;
		
		$type = Type::intersect($types);
		if (!$type) return;*/
		//if ($type) echo "{$this->details()} \033[1mvalid for types\033[0m: {$type->details()}\n";
	}
}