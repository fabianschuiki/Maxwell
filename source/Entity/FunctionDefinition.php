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
		$e->setBody(Block::makeFromSyntaxNode($def->getBody()));
		return $e;
	}
	
	protected $name;
	protected $body;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setBody(Block $b) { $this->body = $b; }
	public function getBody() { return $this->body; }
}