<?php
namespace LET;

class ConcreteType_Intf extends ConcreteType
{
	public $name;
	public $members;
	
	public function __construct(Scope $scope, ConcreteType $type)
	{
		if (!$type->subscope) {
			echo "missing subscope for ".get_class($type)."\n";
			debug_print_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS);
		}
		$subscope = $type->subscope->reduceToInterface($scope);
		
		$members = array();
		foreach ($type->members() as $member) {
			$members[] = $member->reduceToInterface($subscope);
		}
		
		$this->name     = strval($type->name());
		$this->members  = $members;
		$this->subscope = $subscope;
		$this->scope    = $scope;
	}
	
	public function name()    { return $this->name; }
	public function members() { return $this->members; }
	
	public function reduceToInterface() { throw new \RuntimeException("ConcreteType_Intf should never be asked for reduction"); }
	
	public function specialize(MemberConstrainedType $type, array &$specializations)
	{
		if (!$this->specializations) $this->specializations = array();
		if (in_array($type, $this->specializations)) return $type;
		$this->specializations[] = $type;
		
		$root = $this->scope->rootNode();
		assert($root instanceof Root);
		\mwc\debug("asked to specialize external type {$type->details()} at ".get_class($root)."\n");
		$root->specializations[] = $type->reduceToInterface(new Scope);
		return $type;
	}
}