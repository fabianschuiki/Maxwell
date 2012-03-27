<?php
namespace LET;

abstract class Ident extends Expr
{
	public $boundTo;
	
	abstract function name();
	
	public function details()  { return $this->name(); }
	public function children() { return array(); } 
	
	public function bind()
	{
		$nodes = $this->scope->find($this->name());
		
		//TODO: perform type check.
		echo "binding identifier {$this->name()} -> ".count($nodes)." nodes\n";
		
		$this->boundTo = null;
		if (count($nodes) == 1) {
			$this->boundTo = $nodes[0];
		}
	}
	
	public function type()
	{
		if ($this->boundTo instanceof Type) {
			return $this->boundTo;
		}
		if (method_exists($this->boundTo, 'type')) {
			return $this->boundTo->type();
		}
		return null;
	}
	
	public function constraintTarget() { return $this->boundTo; }
}