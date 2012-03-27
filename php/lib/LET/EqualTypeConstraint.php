<?php
namespace LET;

class EqualTypeConstraint extends Constraint
{
	public $nodes;
	
	public function __construct($nodes)
	{
		if (!is_array($nodes)) $nodes = func_get_args();
		foreach ($nodes as $node) assert($node instanceof Node && $node->type() instanceof Type);
		
		$nodes = array_map(function($node){ return $node->constraintTarget(); }, $nodes);
		
		$this->nodes = $nodes;
	}
	
	public function details()
	{
		$nodes = array_map(function($node){ return $node->details(true); }, $this->nodes);
		return '"'.implode('" = "', $nodes).'"';
	}
	
	///Returns whether the constraint is met.
	public function met()
	{
		$nodes = $this->nodes;
		while (count($nodes) > 0) {
			$a = array_shift($nodes);
			foreach ($nodes as $b) {
				if ($a->type() != $b->type()) return false;
			}
		}
		return true;
	}
	
	///Merges the other constraint if they share at least one node. Returns true if a merge occured, false otherwise.
	public function merge(EqualTypeConstraint $other)
	{
		$hasCommon = false;
		foreach ($this->nodes as $a) {
			if (in_array($a, $other->nodes, true)) {
				$hasCommon = true;
				break;
			}
		}
		
		if ($hasCommon) {
			foreach ($other->nodes as $node) {
				if (!in_array($node, $this->nodes, true)) {
					$this->nodes[] = $node;
				}
			}
		}
		
		return $hasCommon;
	}
	
	public function apply()
	{
		$types = array_map(function($node){ return $node->type(); }, $this->nodes);
		if (in_array(null, $types, true)) return;
		
		$type = Type::intersect($types);
		if (!$type) return;
		
		echo " -> \033[1mcommon type\033[0m: {$type->details()}\n";
	}
}