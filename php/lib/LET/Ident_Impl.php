<?php
namespace LET;

class Ident_Impl extends Ident
{
	public $name;
	
	public function __construct(Scope $scope, $name)
	{
		$this->name  = $name;
		$this->scope = $scope;
	}
	
	public function name() { return $this->name; }
}