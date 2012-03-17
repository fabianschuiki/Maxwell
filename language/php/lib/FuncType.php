<?php

class FuncType extends Type
{
	public $in;
	public $out;
	
	public function __construct()
	{
		$this->in  = new TupleType;
		$this->out = new TupleType;
	}
	
	public function __toString()
	{
		return $this->in."->".$this->out;
	}
	
	public function addInput(Type $type, $name = null)
	{
		$this->in->addField($type, $name);
	}
	
	public function addOutput(Type $type, $name = null)
	{
		$this->out->addField($type, $name);
	}
	
	public function match(Type $type, &$vars = array(), $initial = true)
	{
		if (!$type instanceof FuncType) {
			return null;
		}
		
		$match = new FuncType;
		$match->in  = $this->in ->match($type->in,  $vars, false);
		$match->out = $this->out->match($type->out, $vars, false);
		
		if ($initial) {
			$match->resolveVars();
		}
		
		if ($match->in && $match->out) {
			return $match;
		} else {
			return null;
		}
	}
	
	public function resolveVars()
	{
		if ($this->in)  $this->in ->resolveVars();
		if ($this->out) $this->out->resolveVars();
	}
	
	public function isGeneric()
	{
		if ($this->in->isGeneric())  return true;
		if ($this->out->isGeneric()) return true;
		return false;
	}
	
	public function cost()
	{
		return $this->in->cost() + $this->out->cost();
	}
}