<?php
namespace Entity;
use Source\Range;

class Block extends Entity
{
	static public function makeFromSyntaxNode(\AST\Block $block)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($block->getGroup()->getRange());
		
		$s = array();
		foreach ($block->getStmts() as $stmt) {
			$s[] = Stmt\Stmt::makeFromSyntaxNode($stmt);
		}
		$e->setStmts($s);
		
		return $e;
	}
	
	protected $stmts;
	
	public function setStmts($s) { $this->stmts = $s; }
	public function getStmts() { return $this->stmts; }
}