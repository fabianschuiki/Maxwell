<?php
namespace LET;

class Func_Proxy extends Func
{
	public function __construct($id)
	{
		parent::__construct();
		assert(is_string($id) || is_numeric($id));
		$this->id = $id;
	}
	
	public function name() { return "<proxy>"; }
	
	public function details() { return "@".$this->id; }
	
	public function reduceToAbsolute(Scope $scope) { throw new \RuntimeException("Func_Proxy should never be asked for absolute reduction"); }
}