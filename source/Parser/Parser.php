<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenList;
use IssueList;
use Language;

class Parser
{
	protected $tokens;
	protected $nodes;
	
	public function __construct(TokenList $tokens)
	{
		$this->tokens = $tokens;
	}
	
	public function run()
	{
		$nodes = array();
		$tokens = $this->tokens->getStripped();
		while (!$tokens->isEmpty()) {
			$stmt = static::parseStmt($tokens);
			if ($stmt) $nodes[] = $stmt;
		}
		$this->nodes = $nodes;
	}
	
	static protected function parseStmt(TokenList $tokens)
	{
		if ($tokens->is(0, 'identifier') && in_array($tokens->getText(), Language::$keywords)) {
			return static::parseKeywordStmt($tokens->consume(), $tokens);
		}
		
		//As a last resort, simply consume one token and throw an error.
		$token = $tokens->consume();
		IssueList::add('error', "Unable to parse statement starting with {$token->getNice()}.", $token);
		return null;
	}
	
	static protected function parseKeywordStmt(Token $keyword, TokenList $tokens)
	{
		switch ($keyword->getText()) {
			case 'import': {
				$names = array();
				do {
					if (!$tokens->is(0, 'identifier')) {
						IssueList::add('error', "Imported entity name must be an identifier.", $tokens->consume());
						return null;
					}
					$names[] = $tokens->consume();
				} while ($tokens->is(0, 'symbol', ',') && $tokens->consume());
				return new AST\Stmt\Import($keyword, $names, $tokens->consumeIf('symbol', ';'));
			} break;
			
			case 'package': {
				if (!$tokens->is(0, 'identifier')) {
					IssueList::add('error', "Package name required after keyword 'package'.", $keyword);
					return null;
				}
				return new AST\Stmt\Package($keyword, $tokens->consume(), $tokens->consumeIf('symbol', ';'));
			} break;
		}
		
		//Throw an error if the keyword does not introduce any useful statement.
		IssueList::add('error', "Keyword '{$keyword->getText()}' does not introduce a statement.", $keyword);
		return null;
	}
}