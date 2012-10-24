<?php
namespace Entity\Expr\Call;

class Argument extends \Entity\Entity
{
	static public function makeFromSyntaxNode(\AST\Expr\CallArg $node)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($node->getRange());
		if ($n = $node->getName()) $e->setName($n->getText());
		if ($x = $node->getExpr()) $e->setExpr(\Entity\Expr\Expr::makeFromSyntaxNode($x));
		return $e;
	}
	
	protected $name;
	protected $expr;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setExpr(\Entity\Expr\Expr $e) { $this->expr = $e; }
	public function getExpr() { return $this->expr; }
	
	public function getChildEntities() { return array($this->expr); }
}