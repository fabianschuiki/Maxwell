<?php
namespace LET;

class TypeExpr extends Type
{
	public $expr;
	
	public function __construct(Scope $scope, Expr $expr)
	{
		$this->expr  = $expr;
		$this->scope = $scope;
	}
	
	public function expr() { return $this->expr; }
	
	public function details()
	{
		return ($this->expr ? $this->expr->details() : '?');
	}
	
	public function reduce()
	{
		if ($this->expr instanceof Ident) {
			$type = $this->expr->type();
			if ($type instanceof ConcreteType) return $type;
		}
		return $this;
	}
}