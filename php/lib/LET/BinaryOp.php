<?php
namespace LET;

class BinaryOp extends Call
{
	public $asn;
	public $op;
	public $lhs;
	public $rhs;
	
	public function __construct(Scope $scope, \AST\BinaryOpExpr $node)
	{
		$this->asn   = $node;
		$this->op    = new Ident_Impl($scope, $node->op->text);
		$this->lhs   = Expr::make($scope, $node->lhs);
		$this->rhs   = Expr::make($scope, $node->rhs);
		$this->scope = $scope;
	}
	
	public function callee() { return $this->op; }
	public function args()   { return array($this->lhs, $this->rhs); }
}