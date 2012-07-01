<?php
namespace Lexer;

class TokenList
{
	protected $tokens = array();
	
	public function add(AbstractToken $t)
	{
		$this->tokens[] = $t;
	}
	
	public function isEmpty()
	{
		return count($this->tokens) == 0;
	}
	
	public function isIndexValid($index)
	{
		return ($index >= 0 && $index < count($this->tokens));
	}
	
	public function is($type, $text = null, $index = 0)
	{
		if (!$this->isIndexValid($index)) return false;
		return $this->tokens[$index]->is($type, $text);
	}
	
	public function count()
	{
		return count($this->tokens);
	}
	
	public function getText($index = 0)
	{
		if (!$this->isIndexValid($index))
			trigger_error("Trying to get text of token at index $index, which is out of bounds", E_USER_ERROR);
		return $this->tokens[$index]->getText();
	}
	
	public function consume()
	{
		if ($this->isEmpty())
			trigger_error("Trying to consume token, but list is empty", E_USER_ERROR);
		return array_shift($this->tokens);
	}
	
	public function consumeIf($type, $text)
	{
		if ($this->is($type, $text))
			return $this->consume();
		return null;
	}
	
	public function getTokens() { return $this->tokens; }
	
	public function getStripped()
	{
		$list = new TokenList;
		foreach ($this->tokens as $t) {
			if ($t->is('whitespace') || $t->is('comment')) continue;
			$list->add($t);
		}
		return $list;
	}
	
	public function upTo($type, $text = null)
	{
		$list = new TokenList;
		while (!$this->isEmpty()) {
			if ($this->is($type, $text))
				break;
			$list->add($this->consume());
		}
		return $list;
	}
}