<?php
namespace LET;

class CallArg_AST extends CallArg
{
	public $asn;
	public $expr;
	
	public function __construct(Scope $scope, \AST\CallArg $arg)
	{
		$this->asn   = $arg;
		$this->expr  = Expr::make($scope, $arg->expr);
		$this->scope = $scope;
	}
	
	public function name() { return $this->asn->name->text; }
	public function expr() { return $this->expr; }
}