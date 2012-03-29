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
		$nodes = $this->scope->find($this->name());
		
		//TODO: perform type check.
		echo "binding identifier {$this->name()} -> ".count($nodes)." nodes\n";
		
		$boundTo = null;
		if (count($nodes) == 0) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Entity '{$this->name()}' is unknown.",
				$this
			);
		}
		if (count($nodes) == 1) $boundTo = $nodes[0];
		
		$this->boundTo    = $boundTo;
		$this->boundNodes = $nodes;
	}
	
	public function type()
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