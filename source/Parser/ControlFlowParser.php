<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenGroup;
use Lexer\TokenList;
use IssueList;
use Language;

class ControlFlowParser
{
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
		$body = StatementParser::parseBlockOrStmt($tokens);
		
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
		$body = StatementParser::parseBlockOrStmt($tokens);
		if (!$body) return null;
		return new AST\Stmt\ElseStmt($keyword, $body);
	}

	static public function parseForStmt(Token $keyword, TokenList $tokens)
	{
		if (!$tokens->is("group", "()")) {
			IssueList::add('error', "'for' statement requires an initial expression, loop condition and increment expression in paranthesis.", $keyword);
			return null;
		}
		$cfg_group = $tokens->consume();
		$cfg_tokens = $cfg_group->getStrippedTokens();

		$body = StatementParser::parseBlockOrStmt($tokens);

		$initial_tokens = $cfg_tokens->upTo('symbol', ';');
		if ($cfg_tokens->consumeIf('symbol', ';')) {
			$condition_tokens = $cfg_tokens->upTo('symbol', ';');
			if ($cfg_tokens->consumeIf('symbol', ';')) {
				$increment_tokens = $cfg_tokens->upTo('symbol', ';');
			} else {
				IssueList::add('error', "Either a condition expression, or an initial expression, loop condition and increment expression required in for loop statement.", $cfg_group);
				return null;
			}
		} else {
			$condition_tokens = $initial_tokens;
			$initial_tokens = null;
			$increment_tokens = null;
		}

		$initial   = ($initial_tokens   ? ExpressionParser::parseExpr($initial_tokens)   : null);
		$condition = ($condition_tokens ? ExpressionParser::parseExpr($condition_tokens) : null);
		$increment = ($increment_tokens ? ExpressionParser::parseExpr($increment_tokens) : null);

		//Catch additional superfluous tokens in the configuration group.
		if (!$cfg_tokens->isEmpty()) {
			IssueList::add('warning', "Superfluous tokens in for loop statement ignored.", $cfg_tokens->getTokens());
		}

		if (!$condition || !$body) return null;
		return new AST\Stmt\ForStmt($keyword, $initial, $condition, $increment, $body, $cfg_group);
	}
}