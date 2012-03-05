<?php

class FuncType
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
	
	public function addInput(TypeSet $type, $name = null)
	{
		$this->in->addField($type, $name);
	}
	
	public function addOutput(TypeSet $type, $name = null)
	{
		$this->out->addField($type, $name);
	}
}