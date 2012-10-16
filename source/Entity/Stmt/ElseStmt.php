<?php
namespace Entity\Stmt;
use Entity\Scope\Scope;

class ElseStmt extends Stmt
{
	static public function makeFromSyntaxNode(\AST\Stmt\ElseStmt $stmt)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($stmt->getRange());
		$e->setHumanRange($stmt->getKeyword()->getRange());
		$e->setBody(\Entity\Block::makeFromSyntaxNode($stmt->getBody()));
		return $e;
	}
	
	protected $body;
	protected $scope;
	
	public function setBody(\Entity\Block $b) { $this->body = $b; }
	public function getBody() { return $this->body; }
	
	public function setScope(Scope $s) { $this->scope = $s; }
	public function getScope() { return $this->scope; }
	
	public function initScope(Scope $scope)
	{
		$this->setScope($scope);
		$this->body->initScope($scope);
	}
	
	public function getChildEntities() { return array($this->body); }
}