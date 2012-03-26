<?php
namespace LET;

abstract class Ident extends Expr
{
	abstract function name();
	
	public function details()
	{
		return $this->name();
	}
	
	public function bind()
	{
		$nodes = $this->scope->find($this->name());
		echo "binding identifier {$this->name()} -> ".count($nodes)." nodes\n";
	}
}