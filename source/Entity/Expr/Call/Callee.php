<?php
namespace Entity\Expr\Call;

class Callee extends \Entity\Entity
{
	static public function makeFromSyntaxNode(\AST\Expr\Expr $node)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($node->getRange());
		$e->setExpr(\Entity\Expr\Expr::makeFromSyntaxNode($node));
		return $e;
	}
	
	protected $expr;
	
	public function setExpr(\Entity\Expr\Expr $e) { $this->expr = $e; }
	public function getExpr() { return $this->expr; }
	
	public function initScope(\Entity\Scope\Scope $scope)
	{
		$this->expr->initScope($scope);
	}
	
	public function getChildEntities() { return array(); }
}