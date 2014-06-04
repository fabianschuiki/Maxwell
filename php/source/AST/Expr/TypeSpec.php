<?php
namespace AST\Expr;
use Lexer\Token;
use Lexer\TokenGroup;

class TypeSpec extends Expr
{
	protected $expr;
	protected $args;
	protected $group;
	
	public function __construct(Expr $expr, array $args, TokenGroup $group)
	{
		parent::__construct();

		foreach ($args as $arg) {
			if (!$arg instanceof Expr) {
				throw new \RuntimeException("Argument ".vartype($arg)." to type specialization is not a valid AST\Expr.");
			}
		}

		$this->expr = $expr;
		$this->args = $args;
		$this->group = $group;
	}
	
	public function getExpr() { return $this->expr; }
	public function getArgs() { return $this->args; }
	public function getGroup() { return $this->group; }
}