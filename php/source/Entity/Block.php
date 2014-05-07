<?php
namespace Entity;
use Source\Range;

class Block extends Entity
{
	static public function makeFromSyntaxNode(\AST\Block $block)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($block->getRange());
		
		$s = array();
		foreach ($block->getStmts() as $stmt) {
			$s[] = Stmt\Stmt::makeFromSyntaxNode($stmt);
		}
		$e->setStmts($s);
		
		return $e;
	}
	
	protected $stmts;
	protected $headScope;
	protected $tailScope;
	
	public function setStmts($s) { $this->stmts = $s; }
	public function getStmts() { return $this->stmts; }
	
	public function setHeadScope(Scope\Scope $s) { $this->headScope = $s; }
	public function getHeadScope() { return $this->headScope; }
	
	public function setTailScope(Scope\Scope $s) { $this->tailScope = $s; }
	public function getTailScope() { return $this->tailScope; }
	
	public function initScope(Scope\Scope &$outer)
	{
		$scope = new Scope\Scope;
		$scope->generateID();
		$scope->setOuter($outer);
		$this->setHeadScope($scope);
		foreach ($this->getStmts() as $stmt) {
			$stmt->initScope($scope);
		}
		$this->setTailScope($scope);
	}
	
	public function getChildEntities()
	{
		return $this->stmts;
	}
}