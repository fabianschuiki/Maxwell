<?php
namespace Lexer;

class TokenGroup extends AbstractToken
{
	protected $startToken;
	protected $endToken;
	protected $tokens;
	
	public function __construct()
	{
		$this->tokens = new TokenList;
	}
	
	public function getStartToken() { return $this->startToken; }
	public function getEndToken() { return $this->endToken; }
	
	public function getType() { return 'group'; }
	public function getText() { return $this->startToken->getText() . $this->endToken->getText(); }
	public function getRange() { return Range::union($this->startToken->getRange(), $this->endToken->getRange()); }
	public function getFile() { return $this->startToken->getFile(); }
	
	public function getTokens() { return $this->tokens; }
	
	//Only to be used by the Lexer:
	public function setStartToken(Token $t) { $this->startToken = $t; }
	public function setEndToken(Token $t) { $this->endToken = $t; }
	
	public function getRequiredEndSymbol()
	{
		return static::closingSymbolFor($this->startToken->getText());
	}
	
	
	static private $symbolSequence = "()[]{}";
	
	static public function closingSymbolFor($opening)
	{
		for ($i = 0; $i < strlen(static::$symbolSequence)-1; $i++)
			if (static::$symbolSequence[$i] == $opening)
				return static::$symbolSequence[$i+1];
		return null;
	}
	
	static public function openingSymbolFor($closing)
	{
		for ($i = 1; $i < strlen(static::$symbolSequence); $i++)
			if (static::$symbolSequence[$i] == $closing)
				return static::$symbolSequence[$i-1];
		return null;
	}
}
