<?php
namespace AST\Stmt;
use Lexer\Token;
use AST\Block;

class FuncDef extends Keyword
{
	protected $name;
	protected $args_in;
	protected $args_out;
	protected $body;
	
	public function __construct(Token $keyword, Token $name, array $args_in, array $args_out, Block $body = null)
	{
		parent::__construct();
		$this->keyword = $keyword;
		$this->name = $name;
		$this->args_in = $args_in;
		$this->args_out = $args_out;
		$this->body = $body;
	}
	
	public function getName() { return $this->name; }
	public function getArgsIn() { return $this->args_in; }
	public function getArgsOut() { return $this->args_out; }
	public function getBody() { return $this->body; }
}