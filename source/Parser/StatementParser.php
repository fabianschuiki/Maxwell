<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenGroup;
use Lexer\TokenList;
use IssueList;
use Language;

class StatementParser
{
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
	
	static public function parseKeywordStmt(Token $keyword, TokenList $tokens)
	{
		switch ($keyword->getText()) {
			case 'import': {
				$names = array();
				do {
					if (!$tokens->is('identifier')) {
						IssueList::add('error', "Imported entity name must be an identifier.", $tokens->consume());
						return null;
					}
					$names[] = $tokens->consume();
				} while ($tokens->is('symbol', ',') && $tokens->consume());
				return new AST\Stmt\Import($keyword, $names, $tokens->consumeIf('symbol', ';'));
			} break;
			
			case 'package': {
				if (!$tokens->is('identifier')) {
					IssueList::add('error', "Package name required after keyword 'package'.", $keyword);
					return null;
				}
				return new AST\Stmt\Package($keyword, $tokens->consume(), $tokens->consumeIf('symbol', ';'));
			} break;
			
			case 'func': return DefinitionParser::parseFuncDefStmt($keyword, $tokens);
			
			case 'if': return ControlFlowParser::parseIfStmt($keyword, $tokens);
			case 'else': return ControlFlowParser::parseElseStmt($keyword, $tokens);
		}
		
		//Throw an error if the keyword does not introduce any useful statement.
		IssueList::add('error', "Keyword '{$keyword->getText()}' does not introduce a statement.", $keyword);
		return null;
	}
}