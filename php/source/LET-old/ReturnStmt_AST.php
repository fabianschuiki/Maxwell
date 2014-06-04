<?php
namespace LET;

class ReturnStmt_AST extends ReturnStmt
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\ReturnStmt $node)
	{
		if ($node->expr) {
			$expr = Expr::make($scope, $node->expr);
		} else {
			$expr = new Tuple_Impl($scope, array());
		}
		
		parent::__construct($scope, $expr);
		
		$this->asn = $node;
	}
}