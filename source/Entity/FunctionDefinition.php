<?php
namespace Entity;
use Source\Range;

class FunctionDefinition extends RootEntity
{
	static public function makeFromSyntaxNode(\AST\Stmt\FuncDef $def)
	{
		$e = new self;
		$e->generateID();
		$e->setRange(Range::union($def->getKeyword()->getRange(), $def->getBody()->getRange()));
		$e->setHumanRange(Range::union($def->getKeyword()->getRange(), $def->getName()->getRange()));
		$e->setName($def->getName()->getText());
		return $e;
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
}