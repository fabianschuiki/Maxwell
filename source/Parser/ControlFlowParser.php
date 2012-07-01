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
		return null;
	}
}