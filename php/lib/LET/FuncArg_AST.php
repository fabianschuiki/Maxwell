<?php
namespace LET;

class FuncArg_AST extends FuncArg
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\FuncArg $node)
	{
		$this->asn   = $node;
		$this->scope = $scope;
		
		$scope->add($this);
	}
	
	public function type() { return $this->asn->type->name->text; }
	public function name() { return $this->asn->name->text; }
}