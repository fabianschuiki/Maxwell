<?php
namespace AST;

class ImportStmt extends Stmt
{
	public $keyword;
	public $name;
	
	public function __construct(\Token $keyword, \Token $name)
	{
		$this->keyword = $keyword;
		$this->name    = $name;
	}
}