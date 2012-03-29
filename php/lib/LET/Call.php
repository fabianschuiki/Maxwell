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
		
		/*$args = array_map(function($arg){
			return ($arg ? $arg->details() : '?');
		}, $this->args());
		$args = implode(", ", $args);*/
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
	
	///Returns the type of the function referenced by the callee, or null if there is none.
	public function funcType()
	{
		$callee = $this->callee();
		if ($callee) {
			$func = $callee->type();
			if ($func instanceof FuncType) return $func;
		}
		return null;
	}
	
	public function unconstrainedType()
	{
		$type = $this->funcType();
		if ($type) $type = $type->out();
		return $type;
	}
	
	public function spawnConstraints(array &$constraints)
	{
		if (!$this->typeProxy) $this->typeProxy = new CallTypeProxy($this);
		parent::spawnConstraints($constraints);
	}
	
	public function clearConstraints()
	{
		parent::clearConstraints();
		
		//This is somewhat nasty, yet it is required for the callee to filter the functions according to the argument tuple.
		$args = $this->args()->type();
		if (!$args) $args = new GenericType;
		$callee = $this->callee();
		if ($callee) {
			$callee->typeConstraint = new FuncType($this->scope, $args, new GenericType);
			$callee->bind();
			$callee->reduce();
		}
	}
	
	public function imposeConstraint(Constraint $constraint)
	{
		parent::imposeConstraint($constraint);
		
		$callee = $this->callee();
		if ($callee && $constraint->type()) {
			$args = $this->args()->type();
			if (!$args) $args = new GenericType;
			$callee->typeConstraint = new FuncType($this->scope, $args, $constraint->type());
			
			//Gives the callee the chance to update its binding.
			$callee->bind();
			$callee->reduce();
		}
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