<?php
namespace LET;

class Constant_Impl extends Constant
{
	public $value;
	public $dataType;
	
	public function __construct(Scope $scope, $value, $dataType)
	{
		$this->scope = $scope;
		$this->value = $value;
		$this->dataType = $dataType;
		
		parent::__construct();
	}
	
	public function value() { return $this->value; }
	public function dataType() { return $this->dataType; }
}