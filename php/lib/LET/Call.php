<?php
namespace LET;

abstract class Call extends Expr
{
	public $typeProxy;
	
	abstract function callee();
	abstract function args();
	
	public function details()
	{
		$callee = $this->callee();
		$callee = ($callee ? $callee->details() : '?');
		
		$args = $this->args();
		$args = ($args ? $args->details() : '?');
		
		return "'$callee' $args";
	}
	
	public function children()
	{
		$children = array($this->callee(), $this->args());
		if ($this->typeProxy) $children[] = $this->typeProxy;
		return $children;
	}
	
	public function unconstrainedType()
	{
		$callee = $this->callee();
		if ($callee) {
			$func = $callee->type();
			if ($func instanceof FuncType) return $func->out();
		}
		return null;
	}
	
	/// Returns the FuncType requried by this call. It is dictated by the arguments' types and the call's type constraint.
	private function funcType()
	{
		$args = $this->args()->type();
		if (!$args) $args = new GenericType;
		return new FuncType($this->scope, $args, $this->typeConstraint);
	}
	
	private function imposeFuncTypeOnCallee()
	{
		$callee = $this->callee();
		if ($callee) {
			$callee->imposeTypeConstraint($this->funcType());
			/*$callee->bind();
			$callee->reduce();*/
		}
	}
	
	public function spawnConstraints(array &$constraints)
	{
		if (!$this->typeProxy) $this->typeProxy = new CallTypeProxy($this);
		parent::spawnConstraints($constraints);
	}
	
	public function clearConstraints()
	{
		parent::clearConstraints();
		$this->imposeFuncTypeOnCallee();
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		parent::imposeTypeConstraint($type);
		$this->imposeFuncTypeOnCallee();
	}
}

class CallTypeProxy extends TypedNode
{
	public $call;
	
	public function __construct(Call $call)
	{
		$this->call = $call;
	}
	
	public function details()           { return 'proxy'; }
	public function children()          { return array(); }
	public function unconstrainedType() { return new GenericType; }
	
	public function spawnConstraints(array &$constraints)
	{
		parent::spawnConstraints($constraints);
		$constraints[] = new EqualTypeConstraint($this->call->callee(), $this->call->typeProxy);
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		parent::imposeTypeConstraint($type);
		if ($this->call && $type instanceof FuncType) {
			$this->call->args()->imposeTypeConstraint($type->in());
		}
	}
}