<?php
namespace LET;

class FuncArg_Impl extends FuncArg
{
	public $type;
	public $name;
	
	public function __construct(Type $type, $name)
	{
		assert(is_string($name));
		$this->type = $type;
		$this->name = $name;
	}
	
	public function type() { return $this->type->name(); }
	public function name() { return $this->name; }
}