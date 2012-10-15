<?php
namespace Entity\Expr;
use Entity\Scope\Scope;

class Type extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Expr $expr)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($expr->getRange());
		$e->setExpr(Expr::makeFromSyntaxNode($expr));
		return $e;
	}
	
	protected $expr;
	protected $type;
	
	public function setExpr(Expr $e) { $this->expr = $e; }
	public function getExpr() { return $this->expr; }
	
	public function setType(\Type\Type $t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		$this->setScope($scope);
		$this->expr->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->expr); }
}