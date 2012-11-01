<?php
namespace AST\Expr;
use Lexer\Token;
use Lexer\TokenList;

class NativeType extends Expr
{
	protected $operator;
	protected $tokens;
	
	public function __construct(Token $operator, TokenList $tokens)
	{
		parent::__construct();
		$this->operator = $operator;
		$this->tokens = $tokens;
	}
	
	public function getOperator() { return $this->operator; }
	public function getIdent() { return $this->tokens; }
}