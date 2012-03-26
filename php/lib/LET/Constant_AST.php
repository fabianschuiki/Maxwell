<?php
namespace LET;

class Constant_AST extends Constant
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\ConstExpr $node)
	{
		$this->asn   = $node;
		$this->scope = $scope;
	}
	
	public function value() { return $this->asn->value->text; }
	public function type()  { return $this->asn->type; }
}