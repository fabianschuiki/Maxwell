<?php
namespace AST\Expr;
use Lexer\Token;

class NewOp extends Expr
{
	protected $keyword;
	protected $expr;
	
	public function __construct(Token $keyword, Expr $expr)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->expr = $expr;
	}
	
	public function getKeyword() { return $this->keyword; }
	public function getExpr() { return $this->expr; }
}