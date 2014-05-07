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
		if ($tokens->is('identifier') && in_array($tokens->getText(), Language::$statementKeywords)) {
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
					/*if (!$tokens->is('identifier')) {
						IssueList::add('error', "Imported entity name must be an identifier.", $tokens->consume());
						return null;
					}*/
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
			
			case 'external': return static::parseExternalStmt($keyword, $tokens);
			
			case 'func': return DefinitionParser::parseFuncDefStmt($keyword, $tokens);
			case 'type': return DefinitionParser::parseTypeDefStmt($keyword, $tokens);
			
			case 'if': return ControlFlowParser::parseIfStmt($keyword, $tokens);
			case 'else': return ControlFlowParser::parseElseStmt($keyword, $tokens);

			case 'for': return ControlFlowParser::parseForStmt($keyword, $tokens);
		}
		
		IssueList::add('error', "Keyword '{$keyword->getText()}' cannot be used in a statement.", $keyword);
		$tokens->upTo('symbol', ';');
		$tokens->consumeIf('symbol', ';');
		return null;
	}
	
	static public function parseExternalStmt(Token $keyword, TokenList $tokens)
	{
		if (!$tokens->is('string')) {
			IssueList::add('error', "Include path of native header file required after keyword 'external'.", $keyword);
			return null;
		}
		$name = $tokens->consume();
		
		if (!$tokens->is('group', '{}')) {
			IssueList::add('warning', "Statement 'external' requires a list of function and/or type declarations.", array($keyword, $name));
			return null;
		}
		$group = $tokens->consume();
		$declarations = static::parseExternalStmtDeclarations($group->getStrippedTokens());
		$semicolon = $tokens->consumeIf('symbol', ';');
		
		if (!$declarations) return null;
		return new AST\Stmt\External($keyword, $name, $declarations, $group, $semicolon);
	}
	
	static public function parseExternalStmtDeclarations(TokenList $tokens)
	{
		$decls = array();
		while (!$tokens->isEmpty()) {
			$decl = static::parseExternalStmtDeclaration($tokens);
			if ($decl) $decls[] = $decl;
		}
		return $decls;
	}
	
	static public function parseExternalStmtDeclaration(TokenList $tokens)
	{
		//Scan up to the next semicolon, discarding discarding empty token sequences.
		$decl_tokens = $tokens->upTo('symbol', ';');
		if ($decl_tokens->isEmpty()) return null;
		
		$semicolon = null;
		if (!$tokens->is('symbol', ';'))
			IssueList::add('warning', "Semicolon missing after external declaration statement. Assuming one is there.", $decl_tokens->getTokens());
		else
			$semicolon = $tokens->consume();
		
		if (!$decl_tokens->is('identifier') || !in_array($decl_tokens->getText(), array("func"))) {
			IssueList::add('error', "Only functions allowed in external declaration lists.", $decl_tokens->getTokens());
			return null;
		}
		$keyword = $decl_tokens->consume();
		switch ($keyword->getText()) {
			case "func": return DefinitionParser::parseFuncDefStmt($keyword, $decl_tokens, true);
		}
		throw new \exception("Somehow no matching parse function was found for an allowed statement within an external declaration list.");
	}
}