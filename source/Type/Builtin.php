<?php
namespace Type;

class Builtin extends Type
{
	static public $names = array('int', 'float', 'Type', 'String');
	
	static public function makeWithName($name)
	{
		$b = new self;
		//$b->generateId();
		$b->setName($name);
		return $b;
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
}