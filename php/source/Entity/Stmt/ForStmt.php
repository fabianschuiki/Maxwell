<?php
namespace Entity\Stmt;
use Entity\Scope\Scope;

class ForStmt extends Stmt
{
	static public function makeFromSyntaxNode(\AST\Stmt\ForStmt $stmt)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($stmt->getRange());
		$e->setHumanRange(\Source\Range::union($stmt->getKeyword()->getRange(), $stmt->getGroup()->getRange()));
		
		if ($v = $stmt->getInitial()) $e->setInitial(\Entity\Expr\Expr::makeFromSyntaxNode($v));
		$e->setCondition(\Entity\Expr\Expr::makeFromSyntaxNode($stmt->getCondition()));
		if ($v = $stmt->getIncrement()) $e->setIncrement(\Entity\Expr\Expr::makeFromSyntaxNode($v));
		$e->setBody(\Entity\Block::makeFromSyntaxNode($stmt->getBody()));
		
		return $e;
	}
	
	protected $initial;
	protected $condition;
	protected $increment;
	protected $body;
	protected $scope;
	
	public function setInitial(\Entity\Expr\Expr $v = null) { $this->initial = $v; }
	public function getInitial() { return $this->initial; }

	public function setCondition(\Entity\Expr\Expr $v) { $this->condition = $v; }
	public function getCondition() { return $this->condition; }

	public function setIncrement(\Entity\Expr\Expr $v = null) { $this->increment = $v; }
	public function getIncrement() { return $this->increment; }
	
	public function setBody(\Entity\Block $b) { $this->body = $b; }
	public function getBody() { return $this->body; }
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope $scope)
	{
		$s = new Scope;
		$s->generateID();
		$s->setOuter($scope);
		$this->setScope($s);
		if ($this->initial) $this->initial->initScope($s);
		$this->condition->initScope($s);
		if ($this->increment) $this->increment->initScope($s);
		$this->body->initScope($s);
	}
	
	public function getChildEntities()
	{
		$a = array();
		if ($this->initial) $a[] = $this->initial;
		$a[] = $this->condition;
		if ($this->increment) $a[] = $this->increment;
		$a[] = $this->body;
		return $a;
	}
}