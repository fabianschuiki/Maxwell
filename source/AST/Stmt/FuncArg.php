<?php
namespace AST\Stmt;
use Lexer\Token;

class FuncArg extends Stmt
{
	protected $type;
	protected $name;
	
	public function __construct(\AST\Expr\Expr $type = null, Token $name)
	{
		$this->type = $type;
		$this->name = $name;
	}
	
	public function getType() { return $this->type; }
	public function getName() { return $this->name; }
}