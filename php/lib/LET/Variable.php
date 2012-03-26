<?php
namespace LET;

class Variable extends Node
{
	public $asn;
	public $type;
	public $initial;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		$initial = null;
		if ($node->initial) {
			$initial = Expr::make($scope, $node->initial);
		}
		
		$this->asn     = $node;
		$this->type    = new InferredType\Named($node->type->name->text);
		$this->initial = $initial;
		$this->scope   = $scope;
		
		$scope->add($this);
	}
	
	public function type() { return $this->type; }
	public function name() { return $this->asn->name->text; }
	
	public function details()
	{
		return "{$this->type()->details()} {$this->name()}";
	}
}