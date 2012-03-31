<?php
namespace LET;

class Variable extends TypedNode
{
	public $asn;
	public $type;
	public $initial;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		$initial = null;
		if ($node->initial) $initial = Expr::make($scope, $node->initial);
		
		$type = Type::make($scope, $node->type);
		
		$this->asn     = $node;
		$this->type    = $type;
		$this->initial = $initial;
		$this->scope   = $scope;
		
		$scope->add($this);
	}
	
	public function name()              { return $this->asn->name->text; }
	public function range()             { return $this->asn->name->range; }
	public function unconstrainedType() { return $this->type; }
	
	public function details($short = false)
	{
		$type = $this->type();
		$type = ($type ? $type->details() : '?');
		
		$initial = $this->initial;
		if ($initial) $initial = $initial->details();
		
		$str = "$type {$this->name()}";
		if ($initial && !$short) $str .= " = $initial";
		
		return $str;
	}
	
	public function reduce()
	{
		if ($this->type())  $this->type    = $this->type()->reduce();
		if ($this->initial) $this->initial = $this->initial->reduce();
		return $this;
	}
	
	public function spawnConstraints(array &$constraints)
	{
		if ($this->initial) {
			$constraints[] = new EqualTypeConstraint($this, $this->initial);
			$this->initial->spawnConstraints($constraints);
		}
	}
}