<?php
namespace LET;

class NativeFunc_AST extends Func
{
	public $asn;
	public $inputs;
	public $outputs;
	public $subscope;
	
	public function __construct(Scope $scope, \AST\NativeFuncStmt $node)
	{
		parent::__construct();
		
		$inputs  = array();
		$outputs = array();
		$subscope = new Scope($scope, $this);
		
		foreach ($node->args_in as $arg) {
			$i = new FuncArg_AST($subscope, $arg);
			$i->parent = $this;
			$inputs[] = $i;
		}
		foreach ($node->args_out as $arg) {
			$o = new FuncArg_AST($subscope, $arg);
			$o->parent = $this;
			$outputs[] = $o;
		}
		
		$this->asn      = $node;
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		$this->subscope = $subscope;
		$this->scope    = $scope;
		
		$scope->add($this);
	}
	
	public function name()     { return $this->asn->name->text; }
	public function stmts()    { return array(); }
	public function subscope() { return $this->subscope; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
}