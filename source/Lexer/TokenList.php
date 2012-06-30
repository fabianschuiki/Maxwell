<?php
namespace Lexer;

class TokenList
{
	protected $tokens = array();
	
	public function add(AbstractToken $t)
	{
		$this->tokens[] = $t;
	}
	
	public function getTokens() { return $this->tokens; }
}