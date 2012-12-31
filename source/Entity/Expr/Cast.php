<?php
namespace Entity\Expr;
use Entity\Scope\Scope;
use Source\Range;

class Cast extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Cast $cast)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($cast->getRange());
		$e->setHumanRange($cast->getGroup()->getRange());
		$e->setType(Type::makeFromSyntaxNode($cast->getType()));
		$e->setExpr(Expr::makeFromSyntaxNode($cast->getExpr()));
		return $e;
	}
	
	protected $type;
	protected $expr;
	
	public function setType(Type $t) { $this->type = $t; $t->setParent($this); }
	public function getType() { return $this->type; }
	
	public function setExpr(Expr $e) { $this->expr = $e; $e->setParent($this); }
	public function getExpr() { return $this->expr; }
	
	public function initScope(Scope &$scope)
	{
		$this->type->initScope($scope);
		$this->expr->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->type, $this->expr); }
	
	public function replaceChild(Entity $child, Entity $with)
	{
		if ($child === $this->type) {
			$this->setType($with);
		} else if ($child === $this->expr) {
			$this->setExpr($with);
		} else {
			throw $this->makeUnknownChildException($child);
		}
	}
}