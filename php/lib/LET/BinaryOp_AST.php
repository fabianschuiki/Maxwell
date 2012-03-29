<?php
namespace LET;

class BinaryOp_AST extends BinaryOp
{
	public $asn;
	public $op;
	public $lhs;
	public $rhs;
	public $args;
	
	public function __construct(Scope $scope, \AST\BinaryOpExpr $node)
	{
		$lhs = Expr::make($scope, $node->lhs);
		$rhs = Expr::make($scope, $node->rhs);
		
		$this->asn   = $node;
		$this->op    = new Ident_Impl($scope, $node->op);
		$this->lhs   = $lhs;
		$this->rhs   = $rhs;
		$this->args  = new Tuple_Impl($scope, array($lhs, $rhs));
		$this->scope = $scope;
	}
	
	public function callee() { return $this->op; }
	public function args()   { return $this->args; }
}