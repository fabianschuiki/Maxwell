<?php
namespace AST\Stmt;
use Lexer\Token;
use AST\Block;

class IfStmt extends Keyword
{
	protected $condition;
	protected $body;
	protected $else;
	
	public function __construct(Token $keyword, \AST\Expr\Expr $condition, Block $body, ElseStmt $else = null)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->condition = $condition;
		$this->body = $body;
		$this->else = $else;
	}
	
	public function getCondition() { return $this->condition; }
	public function getBody() { return $this->body; }
	public function getElse() { return $this->else; }
}