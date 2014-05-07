<?php
namespace AST\Expr\Operator;
use Lexer\Token;
use AST\Expr\Expr;

class Unary extends Expr
{
	protected $operator;
	protected $operand;
	
	public function __construct(Token $operator, Expr $operand)
	{
		$this->operator = $operator;
		$this->operand = $operand;
	}
	
	public function getOperator() { return $this->operator; }
	public function getOperand() { return $this->operand; }
}