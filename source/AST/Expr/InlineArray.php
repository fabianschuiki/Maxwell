<?php
namespace AST\Expr;
use Lexer\TokenGroup;

class InlineArray extends Expr
{
	protected $exprs;
	protected $group;

	public function __construct(array $exprs, TokenGroup $group)
	{
		parent::__construct();
		foreach ($exprs as $e) assert($e instanceof Expr);
		$this->exprs = $exprs;
		$this->group = $group;
	}
	
	public function getExprs() { return $this->exprs; }
	public function getGroup() { return $this->group; }
}