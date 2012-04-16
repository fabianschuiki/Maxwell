<?php
namespace LET;

class Func_AST extends Func
{
	public $asn;
	public $inputs;
	public $outputs;
	public $stmts;
	public $subscope;
	
	public function __construct(Scope $scope, \AST\FuncStmt $node, $thisType = null)
	{
		$inputs  = array();
		$outputs = array();
		$subscope = new Scope($scope, $this);
		
		if ($thisType instanceof Type) {
			$i = new FuncArg_Impl($subscope, $thisType, 'this');
			$i->parent = $this;
			$inputs[] = $i;
		}
		
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
		$this->scope    = $scope;
		$this->subscope = $subscope;
		
		$stmts = array();
		if ($node->body instanceof \AST\Block) {
			foreach ($node->body->stmts as $stmt) {
				$s = Node::make($subscope, $stmt);
				if (!$s instanceof ConcreteType_AST && !$s instanceof Func_AST) {
					if ($s) {
						$stmts[] = $s;
					} else {
						global $issues;
						$issues[] = new \Issue(
							'warning',
							"{$stmt->nice()} is not allowed inside a function. Ignored.",
							$stmt
						);
					}
				}
			}
			$stmts = array_filter($stmts);
		} else {
			$e = Expr::make($subscope, $node->body);
			if ($e) $stmts[] = new ReturnStmt($subscope, $e);
		}
		$this->stmts = $stmts;
		
		$scope->add($this);
	}
	
	public function name()     { return $this->asn->name->text; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function stmts()    { return $this->stmts; }
	public function subscope() { return $this->subscope; }
	public function range()    { return $this->asn->name->range; }
}