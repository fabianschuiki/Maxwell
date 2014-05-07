<?php
namespace AST\Expr;
use Lexer\Token;

class Identifier extends Expr
{
	protected $ident;
	
	public function __construct(Token $ident)
	{
		parent::__construct();
		$this->ident = $ident;
	}
	
	public function getIdent() { return $this->ident; }
}