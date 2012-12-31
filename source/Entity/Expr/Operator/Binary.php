<?php
namespace Entity\Expr\Operator;
use Source\Range;
use Entity\Expr\Expr;
use Entity\Scope;

class Binary extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Operator\Binary $node)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($node->getRange());
		$e->setHumanRange($node->getOperator()->getRange());
		
		$lhs = Expr::makeFromSyntaxNode($node->getLHS());
		$rhs = Expr::makeFromSyntaxNode($node->getRHS());
		if (!$lhs || !$rhs) return null;
		
		$e->setLHS($lhs);
		$e->setOperator($node->getOperator()->getText());
		$e->setRHS($rhs);
		
		return $e;
	}
	
	protected $lhs;
	protected $operator;
	protected $rhs;
	
	public function setLHS(Expr $e) { $this->lhs = $e; }
	public function getLHS() { return $this->lhs; }
	
	public function setOperator($o) { $this->operator = $o; }
	public function getOperator() { return $this->operator; }
	
	public function setRHS(Expr $e) { $this->rhs = $e; }
	public function getRHS() { return $this->rhs; }
	
	public function initScope(Scope\Scope &$scope)
	{
		$this->lhs->initScope($scope);
		$this->rhs->initScope($scope);
	}
	
	public function getChildEntities()
	{
		return array($this->lhs, $this->rhs);
	}
}