<?php
namespace LET;

class TupleBinaryOp extends Func
{
	public $operator;
	public $inputs;
	public $outputs;
	public $subscope;
	
	public function __construct($operator, TypeTuple $type)
	{
		$inputs = array();
		for ($i = 0; $i < 2; $i++) $inputs[] = new FuncArg_Impl($type->scope, $type, '~');
		$outputs = array(new FuncArg_Impl($type->scope, $type, '~'));
		
		$this->operator = $operator;
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		//$this->type = new FuncType($type->scope, new TypeTuple($type->scope, $type, $type), new TypeTuple($type->scope, $type));
		$this->scope    = $type->scope;
		$this->subscope = new Scope;
	}
	
	public function name()     { return $this->operator; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function stmts()    { return array(); }
	public function subscope() { return $this->subscope; }
}