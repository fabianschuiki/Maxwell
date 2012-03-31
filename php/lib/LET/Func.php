<?php
namespace LET;

abstract class Func extends Node
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
	
	public function type()
	{
		return new FuncType($this->scope, $this->argsType($this->inputs()), $this->argsType($this->outputs()));
	}
	
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
	
	public function specialize(FuncType $type)
	{
		if ($this->specializations) {
			foreach ($this->specializations as $spec) if ($spec->type() == $type) return $spec;
		} else {
			$this->specializations = array();
		}
		
		echo "\033[1mspecializing\033[0m {$this->details()} for {$type->details()}:\n";
		$spec = new Func_Spec($this, $type);
		$this->specializations[] = $spec;
		$this->scope->add($spec);
		return $this;
	}
}