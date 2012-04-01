<?php
namespace LET;

class Ident_Impl extends Ident
{
	public $name;
	
	public function __construct(Scope $scope, $name)
	{
		parent::__construct();
		$this->name  = $name;
		$this->scope = $scope;
	}
	
	public function name()  { return strval($this->name); }
	public function range() { return ($this->name instanceof \Token ? $this->name->range : null); }
}