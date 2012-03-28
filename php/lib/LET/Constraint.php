<?php
namespace LET;

abstract class Constraint
{
	public function kind() { return preg_replace('/^'.preg_quote(__NAMESPACE__.'\\').'/', '', get_class($this)); }
	public function desc() { return "{$this->kind()} {$this->details()}"; }
	
	/** Returns the dependency between the two constraints:
	 *   1  if $this depends on $other
	 *   0  if no dependency exists
	 *  -1  if $other depends on $this */
	public function dependency(Constraint $other) { return 0; }
	
	abstract function details();
	
	abstract function met();
	abstract function impose();
	
	abstract function type();
}