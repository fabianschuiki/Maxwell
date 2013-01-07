<?php
namespace AST\Expr;
use Lexer\Token;
use Lexer\TokenGroup;

class Call extends Expr
{
	protected $callee;
	protected $args;
	protected $argsGroup;
	
	public function __construct (Expr $callee, array $args, TokenGroup $argsGroup)
	{
		parent::__construct();
		foreach ($args as $a) assert($a instanceof CallArg);
		$this->callee = $callee;
		$this->args = $args;
		$this->argsGroup = $argsGroup;
	}
	
	public function getCallee() { return $this->callee; }
	public function getArgs() { return $this->args; }
	public function getArgsGroup() { return $this->argsGroup; }
}