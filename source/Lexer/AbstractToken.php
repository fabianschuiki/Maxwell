<?php
namespace Lexer;

abstract class AbstractToken
{
	abstract function getID();
	abstract function getType();
	abstract function getRawText();
	abstract function getRange();
	abstract function getFile();
	
	public function is($type, $text = null) { return ($this->getType() == $type && (!$text || $this->getText() == $text)); }
	public function isSymbol($text = null) { return $this->is('symbol', $text); }
	
	public function getText() { return $this->getRawText(); }
	public function getNice() { return "{$this->getType()} '{$this->getText()}'"; }
}