<?php
namespace Lexer;
use DomDocument, DomElement;

class TokenSerializer
{
	protected $tokens;
	
	public function __construct(TokenList $tokens)
	{
		$this->tokens = $tokens;
	}
	
	public function getXML()
	{
		$doc = new DomDocument('1.0');
		foreach ($this->tokens->getTokens() as $t)
			$this->_getXML($doc, $doc, $t);
		return $doc->saveXML();
	}
	
	private function _getXML(DomDocument $doc, $root, AbstractToken $token)
	{
		$e = $root->appendChild($doc->createElement($token->getType()));
		$e->setAttribute('id', $token->getID());
		
		$ts = $token->getRange()->getStart();
		$te = $token->getRange()->getEnd();
		
		$e->setAttribute('start', "{$ts->getLine()}:{$ts->getColumn()}:{$ts->getOffset()}");
		$e->setAttribute('end', "{$te->getLine()}:{$te->getColumn()}:{$te->getOffset()}");
		
		switch ($token->getType()) {
			case 'group': {
				foreach ($token->getTokens()->getTokens() as $t)
					$this->_getXML($doc, $e, $t);
			} break;
		}
	}
}