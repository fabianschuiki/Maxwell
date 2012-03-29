<?php
namespace LET;

abstract class Ident extends Expr
{
	public $boundTo;
	public $boundNodes;
	
	abstract function name();
	
	public function details()  { return $this->name(); }
	public function children() { return array(); }
	
	public function bind()
	{
		global $issues;
		$nodes = $this->scope->find($this->name());
		$unfiltered = $nodes;
		if (count($unfiltered) == 0) {
			$issues[] = new \Issue(
				'error',
				"Entity '{$this->name()}' is unknown.",
				$this
			);
		}
		
		$type = $this->typeConstraint;
		if ($type) {
			$nodes = array_filter($nodes, function($node) use ($type) { return Type::intersect($node->type(), $type) != null; });
		}
		echo "binding identifier {$this->name()} -> ".count($unfiltered)." nodes, ".count($nodes)." match type.\n";
		
		$boundTo = null;
		if (count($nodes) == 0 && count($unfiltered) > 0) {
			$issues[] = new \Issue(
				'error',
				"No entity named '{$this->name()}' is of type '{$type->details()}'. Candidates are:",
				$this,
				$unfiltered
			);
		}
		if (count($nodes) == 1) $boundTo = $nodes[0];
		
		$this->boundTo    = $boundTo;
		$this->boundNodes = $nodes;
	}
	
	public function unconstrainedType()
	{
		if ($this->boundTo instanceof Type) {
			return $this->boundTo;
		}
		if (method_exists($this->boundTo, 'type')) {
			return $this->boundTo->type();
		}
		if (is_array($this->boundNodes)) {
			$type = new GenericType;
			foreach ($this->boundNodes as $node) {
				if (!method_exists($node, 'type')) continue;
				$other = $node->type();
				if (!$other) continue;
				
				if ($type instanceof FuncType && $other instanceof FuncType) {
					$in  = Type::intersect($type->in(),  $other->in());
					$out = Type::intersect($type->out(), $other->out());
					if (!$in)  $in  = new GenericType;
					if (!$out) $out = new GenericType;
					$type = new FuncType($this->scope, $in, $out);
				} else {
					$type = Type::intersect($type, $node->type());
				}
			}
			return $type;
		}
		return null;
	}
	
	public function constraintTarget() { return $this->boundTo; }
}