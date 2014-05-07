<?php
namespace AST\Expr;
use Lexer\Token;

class Constant extends Expr
{
	protected $value;
	
	public function __construct(Token $value)
	{
		$this->value = $value;
	}
	
	public function getValue() { return $this->value; }
}