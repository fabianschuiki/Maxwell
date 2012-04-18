<?php
namespace LET;

class TypeExpr extends Type
{
	public $expr;
	
	public function __construct(Scope $scope, Expr $expr)
	{
		parent::__construct();
		$this->expr  = $expr;
		$this->scope = $scope;
	}
	
	public function expr() { return $this->expr; }
	
	public function details()
	{
		return ($this->expr ? '"'.$this->expr->details().'"' : '?');
	}
	
	public function reduce()
	{
		if ($this->expr instanceof TypedNode) {
			$type = $this->expr->type();
			if ($type) return $type;
		}
		return $this;
	}
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new TypeExpr($scope, $this->expr->reduceToAbsolute($scope));
	}
}