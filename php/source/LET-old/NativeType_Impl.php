<?php
namespace LET;

class NativeType_Impl extends NativeType
{
	public $name;
	
	public function __construct(Scope $scope, $name)
	{
		parent::__construct();
		$this->name  = $name;
		$this->scope = $scope;
	}
	
	public function name() { return $this->name; }
}