<?php
namespace LET;

class ConcreteType_Proxy extends ConcreteType
{
	public function __construct($id)
	{
		parent::__construct();
		assert(is_string($id) || is_numeric($id));
		$this->id = $id;
	}
	
	public function name() { return "<proxy>"; }
	public function members() { return array(); }
	
	public function details() { return "@".$this->id; }
	
	public function reduceToAbsolute(Scope $scope) { throw new \RuntimeException("ConcreteType_Proxy should never be asked for absolute reduction"); }
	
	public function reduce()
	{
		\mwc\debug("type proxy {$this->id} asked to reduce\n");
		return $this;
	}
}