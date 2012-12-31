<?php
namespace AST\Expr;
use Lexer\Token;

class CallArg extends \AST\Node
{
	protected $name;
	protected $expr;
	
	public function __construct(Expr $expr, Token $name = null)
	{
		$this->name = $name;
		$this->expr = $expr;
	}
	
	public function getName() { return $this->name; }
	public function getExpr() { return $this->expr; }
}