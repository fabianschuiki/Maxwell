<?php
namespace Entity\Expr;
use Entity\Scope\Scope;

class NewOp extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\NewOp $op)
	{
		$e = new self;
		$e->generateID();
		$e->setHumanRange($op->getKeyword()->getRange());
		$e->setExpr(Expr::makeFromSyntaxNode($op->getExpr()));
		$e->setRange($op->getRange());
		return $e;
	}
	
	protected $expr;
	
	public function setExpr(Expr $e) { $this->expr = $e; }
	public function getExpr() { return $this->expr; }
	
	public function initScope(Scope &$scope)
	{
		$this->expr->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->expr); }
}