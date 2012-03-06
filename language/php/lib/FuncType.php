<?php

class FuncType extends Type
{
	public $in;
	public $out;
	
	public function __construct()
	{
		$this->in  = new FuncArgsType;
		$this->out = new FuncArgsType;
	}
	
	public function __toString()
	{
		return $this->in." -> ".$this->out;
	}
	
	public function addInput(TypeSet $type, $name = null)
	{
		$this->in->addField($type, $name);
	}
	
	public function addOutput(TypeSet $type, $name = null)
	{
		$this->out->addField($type, $name);
	}
	
	public function intersection(FuncType $type)
	{
		$t = clone $this;
		if (!$t->intersect($type)) {
			return null;
		}
		return $t;
	}
	
	public function intersect(FuncType $type)
	{
		$this->in = $this->in->intersection($type->in);
		$this->out = $this->out->intersection($type->out);
		return ($this->in && $this->out);
	}
	
	public function matches(Type $type)
	{
		if (!$type instanceof FuncType) {
			return false;
		}
		return $this->in->matches($type->in) && $this->out->matches($type->out);
	}
	
	public function cost()
	{
		return $this->in->cost() + $this->out->cost();
	}
}