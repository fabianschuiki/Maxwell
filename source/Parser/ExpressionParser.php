<?php
namespace Parser;
use AST;
use Source\Range;
use Lexer\Token;
use Lexer\TokenList;
use IssueList;
use Language;

class ExpressionParser
{
	static public function parseExpr(TokenList $tokens, Range $range = null)
	{
		if ($tokens->count() == 1) {
			if ($tokens->is('identifier')) return new AST\Expr\Identifier($tokens->consume());
		}
		
		IssueList::add('error', "Unable to parse expression.", ($tokens->isEmpty() ? $range : $tokens->getTokens()));
		return null;
	}
}