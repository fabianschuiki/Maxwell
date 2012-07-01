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
		$root = $doc->appendChild($doc->createElement("tokens"));
		foreach ($this->tokens->getTokens() as $t)
			$this->_getXML($doc, $root, $t);
		return $doc->saveXML();
	}
	
	private function _getXML(DomDocument $doc, DomElement $root, AbstractToken $token)
	{
		$e = $root->appendChild($doc->createElement($token->getType()));
		$e->setAttribute('id', $token->getID());
		$e->setAttribute('range', $token->getRange()->toString());
		if ($token->getType() == 'group') {
			foreach ($token->getTokens()->getTokens() as $t)
				$this->_getXML($doc, $e, $t);
		}
	}
}