<?php
namespace AST\Expr;
use Lexer\Token;

class Call extends Expr
{
	protected $callee;
	protected $args;
	
	public function __construct (Expr $callee, array $args)
	{
		parent::__construct();
		foreach ($args as $a) assert($a instanceof CallArg);
		$this->callee = $callee;
		$this->args = $args;
	}
}