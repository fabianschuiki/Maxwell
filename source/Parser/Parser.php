<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenGroup;
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
	
	static public function parseStmt(TokenList $tokens)
	{
		if ($tokens->is('identifier') && in_array($tokens->getText(), Language::$keywords)) {
			return StatementParser::parseKeywordStmt($tokens->consume(), $tokens);
		}
		
		//As a last resort, simply consume one token and throw an error.
		$token = $tokens->consume();
		IssueList::add('error', "Unable to parse statement starting with {$token->getNice()}.", $token);
		return null;
	}
	
	static public function parseBlock(TokenGroup $group)
	{
		$tokens = $group->getStrippedTokens();
		$stmts = array();
		while (!$tokens->isEmpty()) {
			$stmt = static::parseStmt($tokens);
			if ($stmt) $stmts[] = $stmt;
		}
		return new AST\Block($group, $stmts);
	}
}