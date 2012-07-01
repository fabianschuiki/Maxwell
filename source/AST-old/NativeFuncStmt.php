<?php
namespace AST;

class NativeFuncStmt extends Stmt
{
	public $keyword;
	public $name;
	public $args_in;
	public $args_out;
	
	public function __construct(\Token $keyword, \Token $name, array $args_in, array $args_out)
	{
		$this->keyword  = $keyword;
		$this->name     = $name;
		$this->args_in  = $args_in;
		$this->args_out = $args_out;
	}
	
	public function nice() { return "Native Function Declaration"; }
}