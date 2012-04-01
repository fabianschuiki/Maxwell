<?php
namespace LET;

abstract class Func extends TypedNode
{
	public $specializations;
	
	abstract function name();
	abstract function inputs();
	abstract function outputs();
	abstract function stmts();
	abstract function subscope();
	
	public function details()
	{
		$det = function($arg){ return $arg->details(); };
		return "'{$this->name()}' (".implode(", ", array_map($det, $this->inputs())).") -> (".implode(", ", array_map($det, $this->outputs())).")";
	}
	
	public function children()
	{
		return array_merge(
			$this->inputs(),
			$this->outputs(),
			$this->subscope()->children(),
			$this->stmts()
		);
	}
	
	public function unconstrainedType()
	{
		return new FuncType($this->scope, $this->argsType($this->inputs()), $this->argsType($this->outputs()));
	}
	
	public function type() { return $this->unconstrainedType(); }
	public function imposeTypeConstraint(Type $type) { trigger_error("Func {$this->details()} should not have type constraints.", E_USER_ERROR); }
	
	private function argsType(array $args)
	{
		$fields = array();
		foreach ($args as $arg) {
			$type = $arg->type();
			if ($type) $fields[$arg->name()] = $type;
		}
		return new TypeTuple($this->scope, $fields);
	}
	
	public function isSpecific()
	{
		return $this->type()->isSpecific();
	}
	
	public function specialize(FuncType $type, array &$specializations)
	{
		$thisType = $this->type();
		if (Type::intersect($thisType, $type, $thisType->scope) == $thisType) return $this;
		
		if ($this->specializations) {
			foreach ($this->specializations as $spec) {
				$specType = $spec->type();
				$inter = Type::intersect($specType, $type);
				if ($inter) return $spec;
			}
		} else {
			$this->specializations = array();
		}
		
		foreach (array($type->in(), $type->out()) as $tuple) {
			foreach ($tuple->fields as $name => $arg) {
				if (!$arg instanceof MemberConstrainedType) continue;
				echo "specialization for $name\n";
				$tuple->fields[$name] = $arg->type->specialize($arg, $specializations);
			}
		}
		
		echo "\033[1mspecializing\033[0m {$this->details()} for {$type->details()}\n";
		$spec = new Func_Spec($this, $type);
		$this->specializations[] = $spec;
		$specializations[] = $spec;
		$this->scope->add($spec);
		return $spec;
	}
	
	public function notifyTypeChanged()
	{
		$this->scope->notifyNodeChangedType($this);
	}
	
	/*public function maybeTypeChanged()
	{
		$type = $this->type();
		if ($type != $this->lastConfirmedType && $this->lastConfirmedType) {
			echo "\033[32;1mtype changed\033[0m for {$this->desc()}\n";
			$this->scope->notifyNodeChangedType($this);
		}
		$this->lastConfirmedType = $type;
	}*/
}