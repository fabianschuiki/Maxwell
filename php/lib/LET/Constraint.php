<?php
namespace LET;

abstract class Constraint
{
	public function kind() { return preg_replace('/^'.preg_quote(__NAMESPACE__.'\\').'/', '', get_class($this)); }
	public function desc() { return "{$this->kind()} {$this->details()}"; }
	
	public function dependency(Constraint $other) { return 0; }
	
	abstract function details();
	
	abstract function met();
	abstract function impose();
	
	abstract function type();
}