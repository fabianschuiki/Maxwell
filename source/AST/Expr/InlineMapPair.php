<?php
namespace AST\Expr;
use Lexer\Token;

class InlineMapPair extends Expr
{
	protected $key;
	protected $value;
	
	public function __construct(Token $key, \AST\Expr\Expr $value)
	{
		$this->key = $key;
		$this->value = $value;
	}
	
	public function getKey() { return $this->key; }
	public function getValue() { return $this->value; }
}