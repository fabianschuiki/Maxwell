<?php
namespace Lexer;
use Source\File;
use Source\Location;
use Source\Range;
use Language;
use IssueList;

class Lexer
{
	protected $file;
	protected $tokens;
	
	public function __construct(File $file)
	{
		$this->file = $file;
	}
	
	public function run()
	{
		$contents = $this->file->getContents();
		$len = strlen($contents);
		
		$id = 0;
		$tokens = array();
		$tokenType = null;
		$tokenStart = new Location;
		$tokenEnd   = new Location;
		
		$context = 'normal';
		$pc = 0;
		for ($i = 0; $i < $len + 1; $i++) {
			$c   = ($i   < $len ? $contents[$i]   : null);
			$nc  = ($i+1 < $len ? $contents[$i+1] : null);
			
			$charType = static::getTypeOfChar($c);
			switch ($context) {
				case 'normal': {
					if ($c == '/' && $nc == '/') {
						$charType = 'comment';
						$context = 'comment.single';
					}
					else if ($c == '/' && $nc == '*') {
						$charType = 'comment';
						$context = 'comment.multi';
					}
					else if ($c == '"') {
						$charType = 'string';
						$context = 'string';
					}
					
					//Numbers consume certain non-numeric characters such as '.', 'e', 'E', etc.
					if ($tokenType == 'number' && strchr('.eE', $c) !== false)
						$charType = 'number';
				} break;
				
				case 'comment.single': {
					if ($c == "\n")
						$context = 'normal';
					$charType = 'comment';
				} break;
				
				case 'comment.multi': {
					if ($pc == '*' && $c == '/')
						$context = 'normal';
					$charType = 'comment';
				} break;
				
				case 'string': {
					if ($pc != '\\' && $c == '"')
						$context = 'normal';
					$charType = 'string';
				} break;
			}
			
			$wrapUp = false;
			if ($tokenType == 'symbol')
				$wrapUp = true;
			
			//If the char type does not fit the token type anymore, wrap up the token and start a new one.
			if ($tokenType != $charType || $wrapUp) {
				if ($tokenType != null) {
					$range = new Range($this->file, $tokenStart, $tokenEnd);
					$text = substr($contents, $range->getPosition(), $range->getLength());
					
					$t = new Token($id++, $tokenType, $text, $range);
					$tokens[] = $t;
				}
				
				//Start the new token.
				$tokenType = $charType;
				$tokenStart = clone $tokenEnd;
			}
			
			//Increase the buffer end location.
			if ($c == "\n")
				$tokenEnd->addLine();
			else
				$tokenEnd->addColumn();
			
			$pc = $c;
		}
		
		//Group the tokens.
		$groupStack = array();
		$groupedTokens = new TokenList;
		foreach ($tokens as $t) {
			if ($t->is('symbol') && strchr('([{', $t->getText()) !== false) {
				$g = new TokenGroup($id++);
				$g->setStartToken($t);
				if (count($groupStack) == 0)
					$groupedTokens->add($g);
				else
					end($groupStack)->getTokens()->add($g);
				array_push($groupStack, $g);
			}
			else if ($t->is('symbol') && strchr(')]}', $t->getText()) !== false) {
				if (count($groupStack) == 0) {
					$o = TokenGroup::openingSymbolFor($t->getText());
					IssueList::add('error', "Closing symbol '{$t->getText()}' without prior opening '$o'.", $t->getRange());
					continue; //or maybe return or something
				}
				$g = end($groupStack);
				if ($t->getText() != $g->getRequiredEndSymbol()) {
					IssueList::add('error', "'{$t->getText()}' is not the valid closing symbol for the earlier opening '{$g->getStartToken()->getText()}'.", $t->getRange(), $g->getStartToken()->getRange());
					continue; //or maybe return or something
				}
				$g->setEndToken($t);
				array_pop($groupStack);
			}
			else {
				if (count($groupStack) == 0)
					$groupedTokens->add($t);
				else
					end($groupStack)->getTokens()->add($t);
			}
		}
		
		$this->tokens = $groupedTokens;
	}
	
	static protected function getTypeOfChar($c)
	{
		if (strchr(" \t\n\r", $c) !== false)
			return 'whitespace';
		else if (ord($c) >= 0x30 && ord($c) <= 0x39)
			return 'number';
		else if (in_array($c, Language::$symbols))
			return 'symbol';
		return 'identifier';
	}
	
	public function getFile() { return $this->file; }
	public function getTokens() { return $this->tokens; }
}
