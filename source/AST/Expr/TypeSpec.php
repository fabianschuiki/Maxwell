<?php
namespace AST\Expr;
use Lexer\Token;
use Lexer\TokenGroup;

class TypeSpec extends Expr
{
	protected $name;
	protected $args;
	protected $group;
	
	public function __construct(Token $name, array $args, TokenGroup $group)
	{
		parent::__construct();

		foreach ($args as $arg) {
			if (!$arg instanceof Expr) {
				throw new \RuntimeException("Argument ".vartype($arg)." to type specialization is not a valid AST\Expr.");
			}
		}

		$this->name = $name;
		$this->args = $args;
		$this->group = $group;
	}
	
	public function getName() { return $this->name; }
	public function getArgs() { return $this->args; }
	public function getGroup() { return $this->group; }
}