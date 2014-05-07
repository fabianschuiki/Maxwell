<?php
namespace LET;

class Func_Spec extends Func
{
	public $original;
	public $inputs;
	public $outputs;
	public $stmts;
	public $subscope;
	
	public function __construct(Func $original, FuncType $type)
	{
		parent::__construct();
		
		$subscope = new Scope($original->scope, $this);
		$inputs = array();
		$outputs = array();
		
		foreach ($original->inputs as $input) {
			$i = $input->cloneInto($subscope);
			$i->parent = $this;
			$inputs[] = $i;
		}
		foreach ($original->outputs as $output) {
			$o = $output->cloneInto($subscope);
			$o->parent = $this;
			$outputs[] = $o;
		}
		
		$argNameMap  = function($arg){ return $arg->name(); };
		$inputNames  = array_map($argNameMap, $inputs);
		$outputNames = array_map($argNameMap, $outputs);
		
		$inputPairs  = TypeTuple::fieldPairs($inputNames,  $type->in());
		$outputPairs = TypeTuple::fieldPairs($outputNames, $type->out());
		
		$mapArgTypes = function($args, $pairs, TypeTuple $types) use ($original) {
			foreach ($args as $arg) {
				$fieldType = $types->fields[$pairs[$arg->name()]];
				$arg->type = Type::intersect($arg->type, $fieldType);
				if (!$arg->type) {
					global $issues;
					$issues[] = new \Issue(
						'error',
						"Cannot specialize argument '{$arg->name()}' of function '{$original->name()}' as type '{$fieldType->details()}'.",
						$arg,
						$original
					);
				}
			}
		};
		$mapArgTypes($inputs,  $inputPairs,  $type->in());
		$mapArgTypes($outputs, $outputPairs, $type->out());
		
		$this->original = $original;
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		$this->subscope = $subscope;
		
		$stmts = array();
		foreach ($original->stmts() as $stmt) $stmts[] = $stmt->cloneInto($subscope);
		$stmts = array_filter($stmts);
		$this->stmts = $stmts;
	}
	
	public function name()     { return $this->original->name(); }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function stmts()    { return $this->stmts; }
	public function subscope() { return $this->subscope; }
}