<?php
namespace Interpreter;

class ObjectValue extends Value
{
	public $type;
	public $members;
	
	public function __construct(\LET\ConcreteType $type)
	{
		$members = array();
		foreach ($type->members() as $member) {
			$members[$member->name()] = new Variable($member);
		}
		
		$this->type    = $type;
		$this->members = $members;
	}
	
	public function type() { return $this->type; }
	public function value() { return $this; }
	
	public function valueDetails()
	{
		$str = "{";
		foreach ($this->members as $name => $member) {
			$str .= "\n    $name: $member";
		}
		$str .= "\n}";
		return $str;
	}
}