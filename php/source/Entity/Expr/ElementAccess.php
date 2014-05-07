<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Source\Range;

class ElementAccess extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\ElementAccess $node)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($node->getRange());
		$e->setHumanRange($node->getGroup()->getRange());
		$e->setExpr(Expr::makeFromSyntaxNode($node->getExpr()));
		$e->setIndex(Expr::makeFromSyntaxNode($node->getIndex()));
		return $e;
	}
	
	protected $expr;
	protected $index;
	
	public function setExpr(Expr $e) { $this->expr = $e; }
	public function getExpr() { return $this->expr; }
	
	public function setIndex(Expr $e) { $this->index = $e; }
	public function getIndex() { return $this->index; }
	
	
	public function initScope(Scope &$scope)
	{
		$this->expr->initScope($scope);
		$this->index->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->expr, $this->index); }
}