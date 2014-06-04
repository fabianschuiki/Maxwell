<?php
namespace LET;

class Constant_AST extends Constant
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\ConstExpr $node)
	{
		$this->asn   = $node;
		$this->scope = $scope;
		
		parent::__construct();
	}
	
	public function value()             { return $this->asn->value->text; }
	public function dataType()          { return $this->asn->value->type; }
}