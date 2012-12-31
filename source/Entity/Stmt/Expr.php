<?php
namespace Entity\Stmt;
use Entity\Scope\Scope;
use Source\Range;

class Expr extends Stmt
{
	static public function makeFromSyntaxNode(\AST\Stmt\Expr $node)
	{
		$e = new self;
		$e->generateID();
		
		$expr = \Entity\Expr\Expr::makeFromSyntaxNode($node->getExpr());
		$e->setExpr($expr);
		
		$range = $expr->getRange();
		if ($node->getSemicolon()) $range = Range::union($range, $node->getSemicolon()->getRange());
		$e->setRange($range);
		
		return $e;
	}
	
	protected $expr;
	
	public function setExpr(\Entity\Expr\Expr $e) { $this->expr = $e; }
	public function getExpr() { return $this->expr; }
	
	public function initScope(Scope &$scope)
	{
		$this->expr->initScope($scope);
	}
	
	public function getChildEntities()
	{
		return array($this->expr);
	}
}