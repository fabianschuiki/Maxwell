<?php
namespace LET;

class Tuple_AST extends Expr
{
	public $asn;
	public $exprs;
	
	public function __construct(Scope $scope, \AST\TupleExpr $node)
	{
		$exprs = array();
		foreach ($node->exprs as $name => $expr) {
			$exprs[$name] = Expr::make($scope, $expr);
		}
		$exprs = array_filter($exprs);
		
		$this->asn   = $node;
		$this->exprs = $exprs;
		$this->scope = $scope;
	}
	
	public function details()
	{
		$exprs = array();
		foreach ($this->exprs as $name => $expr) {
			$str = $expr->details();
			if (is_string($name)) $str = "$name: $str";
			$exprs[] = $str;
		}
		$exprs = implode(', ', $exprs);
		
		return "($exprs)";
	}
	
	public function children() { return array_values($this->exprs); }
	
	public function type()
	{
		$fields = array();
		foreach ($this->exprs as $name => $expr) {
			$type = $expr->type();
			if (!$type) return null;
			$fields[$name] = $type;
		}
		return new TypeTuple($this->scope, $fields);
	}
	
	public function resolveConstraints()
	{
		parent::resolveConstraints();
		
		$type = $this->typeConstraint();
		if (!$type instanceof TypeTuple) return;
		
		foreach ($this->exprs as $name => $expr) {
			$constrained = null;
			if (isset($type->fields[$name])) $constrained = $type->fields[$name];
			$expr->typeConstraint = $constrained;
		}
	}
}