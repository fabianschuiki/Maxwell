<?php
namespace LET;

class Func_AST extends Func
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\FuncStmt $node, $thisType = null)
	{
		$inputs  = array();
		$outputs = array();
		
		if ($thisType instanceof Type) {
			$inputs[] = new FuncArg_Impl($thisType, 'this');
		}
		
		foreach ($node->args_in as $arg) {
			$inputs[] = new FuncArg_AST($arg);
		}
		foreach ($node->args_out as $arg) {
			$outputs[] = new FuncArg_AST($arg);
		}
		
		$this->asn     = $node;
		$this->inputs  = $inputs;
		$this->outputs = $outputs;
	}
	
	public function name()    { return $this->asn->name->text; }
	public function inputs()  { return $this->inputs; }
	public function outputs() { return $this->outputs; }
}