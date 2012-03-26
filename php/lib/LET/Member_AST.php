<?php
namespace LET;

class Member_AST extends Member
{
	public $asn;
	public $expr;
	
	public function __construct(Scope $scope, \AST\MemberExpr $node)
	{
		$this->asn = $node;
		$this->expr = Expr::make($scope, $node->expr);
		$this->scope = $scope;
	}
	
	public function expr() { return $this->expr; }
	public function name() { return $this->asn->name->text; }
}