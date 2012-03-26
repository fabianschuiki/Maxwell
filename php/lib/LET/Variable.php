<?php
namespace LET;

class Variable extends Node
{
	public $asn;
	public $initial;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		$initial = null;
		if ($node->initial) {
			$initial = Expr::make($scope, $node->initial);
		}
		
		$this->asn     = $node;
		$this->initial = $initial;
		$this->scope   = $scope;
		
		$scope->add($this);
	}
	
	public function type() { return $this->asn->type->name->text; }
	public function name() { return $this->asn->name->text; }
	
	public function details()
	{
		return "{$this->type()} {$this->name()}";
	}
}