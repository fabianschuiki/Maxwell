<?php
namespace LET;

class Variable extends TypedNode
{
	public $asn;
	public $type;
	public $initial;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		parent::__construct();
		
		$initial = null;
		if ($node->initial) {
			$initial = Expr::make($scope, $node->initial);
			if ($initial) $initial->parent = $this;
		}
		
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
	
	public function nice() { return "Variable '{$this->name()}'"; }
	
	public function reduce()
	{
		parent::reduce();
		if ($this->type())  $this->type    = $this->type()->reduce();
		if ($this->initial) $this->initial = $this->initial->reduce();
		return $this;
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		if ($this->type) $this->type = $this->type->unbindFromInterfaces($root);
		return parent::unbindFromInterfaces($root);
	}
	
	public function spawnConstraints(array &$constraints)
	{
		if ($this->initial) {
			$constraints[] = new EqualTypeConstraint($this, $this->initial);
			$this->initial->spawnConstraints($constraints);
		}
	}
	
	public function buildSpecializations(array &$specializations)
	{
		parent::buildSpecializations($specializations);
		
		$type = $this->type();
		if ($type instanceof MemberConstrainedType && $type->type instanceof ConcreteType) {
			$spec = $type->type->specialize($this->type(), $specializations);
			$this->type = $spec;
		}
	}
	
	/*public function imposeTypeConstraint(Type $type)
	{
		$typeBefore = $this->type();
		parent::imposeTypeConstraint($type);
		$typeAfter  = $this->type();
		if ($typeBefore != $typeAfter) {
			echo "- variable '{$this->name()}' changed type, notifying scope...\n"; 
			$this->propagateTypeChange();
			//$this->scope->notifyNodeChangedType($this);
		}
	}*/
	
	public function notifyTypeChanged()
	{
		$this->scope->notifyNodeChangedType($this);
	}
	
	/*public function notifyNodeChangedType(Node $node)
	{
		parent::notifyNodeChangedType($node);
		if ($node === $this->initial) {
			echo "{$this->desc()} detected initial node {$node->details()} changed type\n";
			$this->propagateTypeChange();
		}
	}*/
	
	/*public function propagateTypeChange()
	{
		parent::propagateTypeChange();
		$this->scope->notifyNodeChangedType($this);
	}*/
}