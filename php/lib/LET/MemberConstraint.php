<?php
namespace LET;

class MemberConstraint extends Constraint
{
	public $node;
	public $members;
	
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
		return $this->node->details(true).".{".implode(', ', $this->members).'}';
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
	
	///Merges the other constraint if they share at least one node. Returns true if a merge occured, false otherwise.
	public function merge(MemberConstraint $other)
	{
		if ($this->node !== $other->node) return false;
		
		$this->members = array_unique(array_merge($this->members, $other->members));
		return true;
	}
	
	public function apply()
	{
		/*$types = array_map(function($node){ return $node->type(); }, $this->nodes);
		if (in_array(null, $types, true)) return;
		
		$type = Type::intersect($types);
		if (!$type) return;
		
		echo " -> \033[1mcommon type\033[0m: {$type->details()}\n";*/
	}
}