<?php
namespace Type;

class Native extends Type
{
	static public function makeWithName($name)
	{
		$b = new self;
		$b->setName($name);
		return $b;
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
}