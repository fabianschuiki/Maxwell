<?php
namespace AST;

class TypeStmt extends Stmt
{
	public $keyword;
	public $name;
	public $body;
	
	public function __construct(\Token $keyword, \Token $name, Block $body)
	{
		assert($keyword->is('keyword'));
		assert($name->is('identifier'));
		$this->keyword = $keyword;
		$this->name    = $name;
		$this->body    = $body;
	}
	
	public function nice() { return "Type definition"; }
}