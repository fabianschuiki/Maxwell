<?php
namespace AST\Stmt;
use Lexer\Token;
use Lexer\TokenGroup;
use AST\Block;

class ForStmt extends Keyword
{
	protected $initial;
	protected $condition;
	protected $increment;
	protected $body;
	protected $group;
	
	public function __construct(Token $keyword, \AST\Expr\Expr $initial = null, \AST\Expr\Expr $condition, \AST\Expr\Expr $increment = null, Block $body, TokenGroup $group)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->initial = $initial;
		$this->condition = $condition;
		$this->increment = $increment;
		$this->body = $body;
		$this->group = $group;
	}
	
	public function getInitial() { return $this->initial; }
	public function getCondition() { return $this->condition; }
	public function getIncrement() { return $this->increment; }
	public function getBody() { return $this->body; }
	public function getGroup() { return $this->group; }
}