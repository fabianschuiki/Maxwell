<?php
namespace LET;

class Variable extends Node
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		$this->asn   = $node;
		$this->scope = $scope;
		
		$scope->add($this);
	}
	
	public function type() { return $this->asn->type->ident->text; }
	public function name() { return $this->asn->name->text; }
	
	public function details()
	{
		return "{$this->type()} {$this->name()}";
	}
}