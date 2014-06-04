<?php
namespace Entity\Expr\Operator;
use Source\Range;
use Entity\Expr\Expr;
use Entity\Scope;
use Entity\Entity;

class Unary extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\Operator\Unary $node)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($node->getRange());
		$e->setHumanRange($node->getOperator()->getRange());
		
		$operand = Expr::makeFromSyntaxNode($node->getOperand());
		if (!$operand) return null;
		
		$e->setOperator($node->getOperator()->getText());
		$e->setOperand($operand);
		
		return $e;
	}
	
	protected $operator;
	protected $operand;
	
	public function setOperator($o) { $this->operator = $o; }
	public function getOperator() { return $this->operator; }
	
	public function setOperand(Expr $e) { $this->operand = $e; $e->setParent($this); }
	public function getOperand() { return $this->operand; }
	
	public function initScope(Scope\Scope &$scope)
	{
		$this->operand->initScope($scope);
	}
	
	public function getChildEntities()
	{
		return array($this->operand);
	}

	public function replaceChild(Entity $child, Entity $with)
	{
		if ($child === $this->operand) {
			$this->setOperand($with);
		} else {
			throw $this->makeUnknownChildException($child);
		}
	}
}