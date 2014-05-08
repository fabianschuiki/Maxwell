<?php
namespace LET;

class PrimitiveBuiltinType extends BuiltinType
{
	public $name;
	
	public function __construct(Scope $scope, $name)
	{
		parent::__construct();
		$this->id = "builtin_type_$name";
		
		assert(is_string($name));
		
		$this->name  = $name;
		$this->scope = $scope;
		
		$scope->add($this);
	}
	
	public function name()    { return $this->name; }
	public function members() { return array(); }
	
	/*public function reduceToAbsolute(Scope $scope)
	{
		return new TypeExpr($scope, new Ident_Impl($scope, $this->name));
	}*/
	
	/*public function unbindFromInterfaces(Root $root)
	{
		return $this->reduceToAbsolute($root->scope);
	}*/
	
	public function gatherExternalNodeIDs(array &$ids)
	{
	}
	
	public function keepOnStack() { return true; }
}