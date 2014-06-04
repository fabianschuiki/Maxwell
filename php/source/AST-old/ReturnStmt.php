<?php
namespace AST;

class ReturnStmt extends Stmt
{
	public $keyword;
	public $expr;
	
	public function __construct(\Token $keyword, $expr)
	{
		assert(!$expr || $expr instanceof Expr);
		$this->keyword = $keyword;
		$this->expr    = $expr;
	}
}