<?php
namespace Entity\Stmt;
use Entity\Scope\Scope;

class IfStmt extends Stmt
{
	static public function makeFromSyntaxNode(\AST\Stmt\IfStmt $stmt)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($stmt->getRange());
		$e->setHumanRange(\Source\Range::union($stmt->getKeyword()->getRange(), $stmt->getCondition()->getRange()));
		
		$e->setCondition(\Entity\Expr\Expr::makeFromSyntaxNode($stmt->getCondition()));
		$e->setBody(\Entity\Block::makeFromSyntaxNode($stmt->getBody()));
		if ($else = $stmt->getElse()) $e->setElse(\Entity\Stmt\ElseStmt::makeFromSyntaxNode($else));
		
		return $e;
	}
	
	protected $condition;
	protected $body;
	protected $else;
	protected $scope;
	
	public function setCondition(\Entity\Expr\Expr $c) { $this->condition = $c; }
	public function getCondition() { return $this->condition; }
	
	public function setBody(\Entity\Block $b) { $this->body = $b; }
	public function getBody() { return $this->body; }
	
	public function setElse(\Entity\Stmt\ElseStmt $e) { $this->else = $e; }
	public function getElse() { return $this->else; }
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope $scope)
	{
		$s = new Scope;
		$s->generateID();
		$s->setOuter($scope);
		$this->setScope($s);
		$this->condition->initScope($s);
		$this->body->initScope($s);
		if ($e = $this->else) $e->initScope($scope);
	}
	
	public function getChildEntities()
	{
		$a = array($this->condition, $this->body);
		if ($this->else) $a[] = $this->else;
		return $a;
	}
}