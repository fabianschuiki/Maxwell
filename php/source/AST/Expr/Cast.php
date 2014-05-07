<?php
namespace AST\Expr;
use Lexer\Token;
use Lexer\TokenGroup;

class Cast extends Expr
{
	protected $type;
	protected $expr;
	protected $group;
	
	public function __construct(Expr $type, Expr $expr, TokenGroup $group)
	{
		parent::__construct();
		$this->type = $type;
		$this->expr = $expr;
		$this->group = $group;
	}
	
	public function getType() { return $this->type; }
	public function getExpr() { return $this->expr; }
	public function getGroup() { return $this->group; }
}