<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenList;
use IssueList;
use Language;

class StatementParser
{
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
			
			case 'func':
				return static::parseFuncDefStmt($keyword, $tokens);
			
			case 'if': return static::parseIfStmt($keyword, $tokens);
			case 'else': return static::parseElseStmt($keyword, $tokens);
		}
		
		//Throw an error if the keyword does not introduce any useful statement.
		IssueList::add('error', "Keyword '{$keyword->getText()}' does not introduce a statement.", $keyword);
		return null;
	}
	
	static public function parseFuncDefStmt(Token $keyword, TokenList $tokens)
	{
		//Extract the function name.
		$name = null;
		if ($tokens->is('identifier')) {
			$name = $tokens->consume();
		}
		else if ($tokens->is('group', '()')) {
			$g = $tokens->consume();
			$gts = $g->getStrippedTokens();
			if ($gts->isEmpty()) {
				IssueList::add('error', "Operator function requires an operator symbol inside the paranthesis.", $g);
				goto name_failed;
			}
			if (!$gts->is('symbol')) {
				IssueList::add('error', "Operator function name needs to be a symbol.", $gts->consume());
				goto name_failed;
			}
			$name = $gts->consume();
			if (!$gts->isEmpty()) {
				IssueList::add('warning', "Operator function should have only one symbol inside the paranthesis. Ignoring additional tokens.", $gts->getTokens(), $name);
			}
		}
		else {
			IssueList::add('error', "Function requires a name or an operator symbol after '{$keyword->getText()}'.", $keyword);
			goto name_failed;
		}
		name_failed:
		
		//Extract the input arguments.
		if ($tokens->is('group', '()'))
			$args_in = static::parseFuncArgs($tokens->consume()->getStrippedTokens());
		else
			$args_in = array();
		
		//Extract the output arguments.
		if ($tokens->consumeIf('symbol', '->') && $tokens->is('group', '()', 1))
			$args_out = static::parseFuncArgs($tokens->consume()->getStrippedTokens());
		else
			$args_out = array();
		
		//Extract the body.
		$body = null;
		if ($tokens->is('group', '{}')) {
			$body = Parser::parseBlock($tokens->consume());
		}
		else {
			IssueList::add('error', "Function requires a body.", array($keyword, $name));
			goto body_failed;
		}
		body_failed:
	}
	
	static public function parseIfStmt(Token $keyword, TokenList $tokens)
	{
		if (!$tokens->is('group', '()')) {
			IssueList::add('error', "'if' statement requires a condition in paranthesis.", $keyword);
			return null;
		}
		$condition_group = $tokens->consume();
		$condition = ExpressionParser::parseExpr($condition_group->getStrippedTokens(), $condition_group->getRange());
		
		if ($tokens->isEmpty()) {
			IssueList::add('error', "'if' statement requires a body.", $keyword);
			return null;
		}
		$body = Parser::parseBlockOrStmt($tokens);
		
		$else = null;
		if ($tokens->is('identifier', 'else')) {
			$else = static::parseElseStmt($tokens->consume(), $tokens);
		}
		
		if (!$condition || !$body) return null;
		return new AST\Stmt\IfStmt($keyword, $condition, $body, $else);
	}
	
	static public function parseElseStmt(Token $keyword, TokenList $tokens)
	{
		if ($tokens->isEmpty()) {
			IssueList::add('error', "'else' statement requires a body.", $keyword);
			return null;
		}
		$body = Parser::parseBlockOrStmt($tokens);
		if (!$body) return null;
		return null;
	}
}