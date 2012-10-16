<?php
namespace Entity\Func;
use Entity\Entity;

class Argument extends Entity
{
	static public function makeFromSyntaxNode(\AST\Stmt\FuncArg $node)
	{
		$e = new self;
		$e->generateID();
		$e->setRange($node->getRange());
		$e->setName($node->getName()->getText());
		if ($t = $node->getType()) $e->setType(\Entity\Expr\Type::makeFromSyntaxNode($t));
		return $e;
	}
	
	protected $name;
	protected $type;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setType(\Entity\Expr\Type $t) { $this->type = $t; }
	public function getType() { return $this->type; }
	
	public function getChildEntities()
	{
		$a = array();
		if ($this->type) $a[] = $this->type;
		return $a;
	}
}