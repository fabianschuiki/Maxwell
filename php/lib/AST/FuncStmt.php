<?php
namespace AST;

class FuncStmt extends Stmt
{
	public $keyword;
	public $name;
	public $args_in;
	public $args_out;
	public $body;
	
	public function __construct(\Token $keyword, \Token $name, array $args_in, array $args_out, Block $body)
	{
		$this->keyword  = $keyword;
		$this->name     = $name;
		$this->args_in  = $args_in;
		$this->args_out = $args_out;
		$this->body     = $body;
	}
}