<?php
namespace LET;

abstract class Call extends Expr
{
	abstract function callee();
	abstract function args();
	
	public function details()
	{
		$callee = $this->callee();
		$callee = ($callee ? $callee->details() : '?');
		
		$args = array_map(function($arg){
			return ($arg ? $arg->details() : '?');
		}, $this->args());
		$args = implode(", ", $args);
		
		return "'$callee' ($args)";
	}
	
	public function children()
	{
		return array_merge(array($this->callee()), $this->args());
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
	
	///Returns the argument type as implied by the arguments.
	public function argType()
	{
		$args = array();
		foreach ($this->args() as $arg) {
			$name = $arg->name();
			$type = $arg->expr();
			if ($type) $type = $type->type();
			if (!$type) {
				$args = null;
				break;
			}
			if ($name) {
				$args[$name] = $type;
			} else {
				$args[] = $type;
			}
		}
		
		return ($args ? new TypeTuple($this->scope, $args) : null);
	}
	
	public function type()
	{
		$type = $this->funcType();
		if ($type) $type = $type->out();
		
		return Type::Intersect($type, $this->typeConstraint);
	}
	
	public function spawnConstraints(array &$constraints)
	{
		//$callee = $this->callee();
		//if ($callee) $constraints[] = new EqualTypeConstraint($this, $callee);
		
		/*$func = $this->funcType();
		if ($func) {
			echo "spawn constraint for {$this->desc()}\n";
			
			$a = $this->funcType();
			if ($a) $a = $a->in;
			$b = $this->argType();
			
			if ($a && $b) {
				$pairs = TypeTuple::fieldPairs($a, $b);
				$args  = $this->args();
				foreach ($pairs as $pair) {
					$at = $a->fields[$pair[0]];
					$arg = $args[$pair[1]];
					if ($at && $bt) 
					echo " -> {$pair[0]} ~ {$pair[1]}\n";
				}
			}
		}*/
	}
	
	public function imposeConstraint(Constraint $constraint)
	{
		parent::imposeConstraint($constraint);
		
		$callee = $this->callee();
		if ($callee && $constraint->type()) {
			$args  = $this->argType();
			if (!$args) $args = new GenericType;
			$callee->typeConstraint = new FuncType($this->scope, $args, $constraint->type());
		}
		
		/*$type = $this->typeConstraint;
		if (!$type instanceof TypeTuple) return;
		
		foreach ($this->exprs as $name => $expr) {
			$constrained = null;
			if (isset($type->fields[$name])) $constrained = $type->fields[$name];
			$expr->typeConstraint = $constrained;
		}*/
	}
}