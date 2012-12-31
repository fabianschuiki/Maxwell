<?php
namespace AST;

class InlineStmt extends Stmt
{
	public $keyword;
	public $body;
	public $code;
	
	public function __construct(\Token $keyword, \TokenGroup $body, $code)
	{
		$this->keyword = $keyword;
		$this->body    = $body;
		$this->code    = $code;
	}
}