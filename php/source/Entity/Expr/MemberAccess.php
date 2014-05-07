<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Source\Range;
use Entity\Entity;

class MemberAccess extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\MemberAccess $ma)
	{
		$e = new self;
		$e->generateID();
		$e->setName($ma->getName()->getText());
		$e->setHumanRange($ma->getName()->getRange());
		$e->setExpr(Expr::makeFromSyntaxNode($ma->getExpr()));
		$e->setRange($ma->getRange());
		return $e;
	}
	
	protected $name;
	protected $expr;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setExpr(Expr $e) { $this->expr = $e; $e->setParent($this); }
	public function getExpr() { return $this->expr; }
	
	
	protected $scope;
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope &$scope)
	{
		$this->setScope($scope);
		$this->expr->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->expr); }
	
	public function replaceChild(Entity $child, Entity $with)
	{
		if ($this->expr === $child) {
			$this->setExpr($with);
		} else {
			throw $this->makeUnknownChildException($child);
		}
	}
}