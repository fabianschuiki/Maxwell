<?php
namespace AST\Expr;
use Lexer\Token;

class TypeVar extends Expr
{
	protected $keyword;
	protected $name;
	
	public function __construct(Token $keyword, Token $name)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->name    = $name;
	}
	
	public function getKeyword() { return $this->keyword; }
	public function getName()    { return $this->name; }
}