<?php
namespace AST\Expr;
use Lexer\Token;
use Lexer\TokenGroup;

class ElementAccess extends Expr
{
	protected $expr;
	protected $index;
	protected $group;
	
	public function __construct(Expr $expr, Expr $index, TokenGroup $group)
	{
		parent::__construct();
		$this->expr = $expr;
		$this->index = $index;
		$this->group = $group;
	}
	
	public function getExpr() { return $this->expr; }
	public function getIndex() { return $this->index; }
	public function getGroup() { return $this->group; }
}