<?php
namespace AST\Expr\Operator;
use Lexer\Token;
use AST\Expr\Expr;

class Binary extends Expr
{
	protected $lhs;
	protected $operator;
	protected $rhs;
	
	public function __construct(Expr $lhs, Token $operator, Expr $rhs)
	{
		$this->lhs = $lhs;
		$this->operator = $operator;
		$this->rhs = $rhs;
	}
	
	public function getLHS() { return $this->lhs; }
	public function getOperator() { return $this->operator; }
	public function getRHS() { return $this->rhs; }
}