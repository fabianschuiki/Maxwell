<?php
namespace LET;

class FuncArg_AST extends FuncArg
{
	public $asn;
	public $type;
	
	public function __construct(Scope $scope, \AST\FuncArg $node)
	{
		$type = Expr::make($scope, $node->type);
		if ($type) $type = new TypeExpr($scope, $type);
		
		$this->asn   = $node;
		$this->type  = $type;
		$this->scope = $scope;
		
		$scope->add($this);
	}
	
	public function type() { return $this->type; }
	public function name() { return $this->asn->name->text; }
	
	public function reduce()
	{
		if ($this->type) $this->type = $this->type->reduce();
		return $this;
	}
}