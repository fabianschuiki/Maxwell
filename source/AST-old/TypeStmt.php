<?php
namespace AST;

class TypeStmt extends Stmt
{
	public $keyword;
	public $name;
	public $parent;
	public $body;
	
	public function __construct(\Token $keyword, \Token $name, $parent, Block $body)
	{
		assert($keyword->is('keyword'));
		assert($name->is('identifier'));
		assert(!$parent || $parent instanceof IdentExpr);
		$this->keyword = $keyword;
		$this->name    = $name;
		$this->parent  = $parent;
		$this->body    = $body;
	}
	
	public function nice() { return "Type definition"; }
}