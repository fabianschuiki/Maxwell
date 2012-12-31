<?php
namespace LET\InferredType;

class Named extends Base
{
	public $name;
	
	public function __construct($name)
	{
		assert(is_string($name));
		$this->name = $name;
	}
	
	public function details()
	{
		return $this->name;
	}
}