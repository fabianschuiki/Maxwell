<?php
namespace LET;

class Func_AST extends Func
{
	public $asn;
	public $stmts;
	public $subscope;
	
	public function __construct(Scope $scope, \AST\FuncStmt $node, $thisType = null)
	{
		$inputs  = array();
		$outputs = array();
		$subscope = new Scope($scope, $this);
		
		if ($thisType instanceof Type) {
			$inputs[] = new FuncArg_Impl($subscope, $thisType, 'this');
		}
		
		foreach ($node->args_in as $arg) {
			$inputs[] = new FuncArg_AST($subscope, $arg);
		}
		foreach ($node->args_out as $arg) {
			$outputs[] = new FuncArg_AST($subscope, $arg);
		}
		
		$stmts = array();
		foreach ($node->body->stmts as $stmt) {
			switch ($stmt->kind()) {
				case 'VarStmt':    $stmts[] = new Variable($subscope, $stmt); break;
				case 'TypeStmt':   new Type_AST($subscope, $stmt); break;
				case 'FuncStmt':   new Func_AST($subscope, $stmt); break;
				case 'ExprStmt':   $stmts[] = Expr::make($subscope, $stmt->expr); break;
				case 'InlineStmt': $stmts[] = new Inline($subscope, $stmt); break;
				default: {
					global $issues;
					$issues[] = new \Issue(
						'warning',
						"{$stmt->nice()} is not allowed inside function '{$node->name}'. Ignored.",
						$stmt
					);
				};
			}
		}
		$stmts = array_filter($stmts);
		
		$this->asn      = $node;
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		$this->stmts    = $stmts;
		$this->scope    = $scope;
		$this->subscope = $subscope;
		
		$scope->add($this);
	}
	
	public function name()    { return $this->asn->name->text; }
	public function inputs()  { return $this->inputs; }
	public function outputs() { return $this->outputs; }
}