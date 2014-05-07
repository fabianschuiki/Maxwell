<?php
namespace AST\Stmt;
use Lexer\Token;
use AST\Block;

class ElseStmt extends Keyword
{
	protected $body;
	
	public function __construct(Token $keyword, Block $body)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->body = $body;
	}
	
	public function getBody() { return $this->body; }
}