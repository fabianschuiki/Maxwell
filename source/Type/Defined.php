<?php
namespace Type;

class Defined extends Type
{
	static public function makeWithDefinition(\Entity\TypeDefinition $d)
	{
		$b = new self;
		//$b->generateId();
		$b->setDefinition($d);
		return $b;
	}
	
	protected $definition;
	
	public function setDefinition(\Entity\TypeDefinition $d) { $this->definition = $d; }
	public function getDefinition() { return $this->definition; }

	public function copy()
	{
		$b = new self;
		$b->setDefinition($this->definition);
		return $b;
	}
}