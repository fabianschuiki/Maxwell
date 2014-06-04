<?php
namespace LET;

class NativeType_AST extends NativeType
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\NativeTypeExpr $node)
	{
		parent::__construct();
		$this->asn   = $node;
		$this->scope = $scope;
	}
	
	public function name() { return $this->asn->name; }
}