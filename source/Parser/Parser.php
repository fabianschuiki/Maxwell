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
		
		//Treat this as an expression statement, i.e. an expression followed by a semicolon.
		$expr_tokens = $tokens->upTo('symbol', ';');
		if ($expr_tokens->isEmpty()) return null;
		
		$semicolon = null;
		if (!$tokens->is('symbol', ';'))
			IssueList::add('warning', "Semicolon missing after expression statement. Assuming one is there.", $expr_tokens->getTokens());
		else
			$semicolon = $tokens->consume();
		
		$expr = ExpressionParser::parseExpr($expr_tokens);
		if (!$expr) return null;
		return new AST\Stmt\Expr($expr, $semicolon);
		
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
		return new AST\Block($stmts, $group);
	}
	
	static public function parseBlockOrStmt(TokenList $tokens)
	{
		if ($tokens->is('group', '{}')) {
			return static::parseBlock($tokens->consume());
		} else {
			$stmt = static::parseStmt($tokens);
			if (!$stmt) return null;
			return new AST\Block(array($stmt));
		}
	}
}