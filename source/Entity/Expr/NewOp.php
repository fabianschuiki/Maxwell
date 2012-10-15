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
		$e->setType(Type::makeFromSyntaxNode($op->getExpr()));
		$e->setRange($op->getRange());
		return $e;
	}
	
	protected $type;
	
	public function setType(Type $e) { $this->type = $e; }
	public function getType() { return $this->type; }
	
	public function initScope(Scope &$scope)
	{
		$this->type->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->type); }
}