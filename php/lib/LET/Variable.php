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
		
		$type = Expr::make($scope, $node->type);
		if ($type) {
			$type = new TypeExpr($scope, $type);
		}
		
		$this->asn     = $node;
		$this->type    = $type;
		$this->initial = $initial;
		$this->scope   = $scope;
		
		$scope->add($this);
	}
	
	public function type() { return $this->type; }
	public function name() { return $this->asn->name->text; }
	
	public function details()
	{
		$type = $this->type();
		if ($type) $type = $type->details();
		
		$initial = $this->initial;
		if ($initial) $initial = $initial->details();
		
		$str = "$type {$this->name()}";
		if ($initial) {
			$str .= " = $initial";
		}
		return $str;
	}
	
	public function reduce()
	{
		if ($this->type) $this->type = $this->type->reduce();
		$this->initial->reduce();
		return $this;
	}
}