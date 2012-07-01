<?php
namespace Parser;
use AST;
use Source\Range;
use Lexer\Token;
use Lexer\TokenGroup;
use Lexer\TokenList;
use IssueList;
use Language;

class ExpressionParser
{
	static public function parseExpr(TokenList $tokens, Range $range = null)
	{
		if ($tokens->count() == 1) {
			if ($tokens->is('identifier')) return new AST\Expr\Identifier($tokens->consume());
			if ($tokens->is('group', '[]')) return static::parseInlineArray($tokens->consume());
			if ($tokens->is('group', '{}')) return static::parseInlineSetOrMap($tokens->consume());
		}
		
		IssueList::add('error', "Unable to parse expression.", ($tokens->isEmpty() ? $range : $tokens->getTokens()));
		return null;
	}
	
	static public function parseInlineArray(TokenGroup $group)
	{
		$tokens = $group->getStrippedTokens();
		$exprs = array();
		while (!$tokens->isEmpty()) {
			$expr_tokens = $tokens->upTo('symbol', ',');
			$comma = $tokens->consumeIf('symbol', ',');
			if ($expr_tokens->isEmpty()) {
				IssueList::add('warning', "Ignoring gratuitous comma. Maybe you forgot to type an array element?", $comma);
				continue;
			}
			$expr = static::parseExpr($expr_tokens);
			if ($expr) $exprs[] = $expr;
		}
		return new AST\Expr\InlineArray($exprs, $group);
	}
	
	static public function parseInlineSetOrMap(TokenGroup $group)
	{
		$tokens = $group->getStrippedTokens();
		if ($tokens->is('symbol', ':', 1))
			return static::parseInlineMap($tokens, $group);
		else
			return static::parseInlineSet($tokens, $group);
	}
	
	static public function parseInlineSet(TokenList $tokens, TokenGroup $group)
	{
		$exprs = array();
		while (!$tokens->isEmpty()) {
			$expr_tokens = $tokens->upTo('symbol', ',');
			$comma = $tokens->consumeIf('symbol', ',');
			if ($expr_tokens->isEmpty()) {
				IssueList::add('warning', "Ignoring gratuitous comma. Maybe you forgot to type a set element?", $comma);
				continue;
			}
			$expr = static::parseExpr($expr_tokens);
			if ($expr) $exprs[] = $expr;
		}
		return new AST\Expr\InlineSet($exprs, $group);
	}
	
	static public function parseInlineMap(TokenList $tokens, TokenGroup $group)
	{
		$pairs = array();
		while (!$tokens->isEmpty()) {
			$pair_tokens = $tokens->upTo('symbol', ',');
			$comma = $tokens->consumeIf('symbol', ',');
			if ($pair_tokens->isEmpty()) {
				IssueList::add('warning', "Ignoring gratuitous comma. Maybe you forgot to type a key-value pair?", $comma);
				continue;
			}
			
			if (!$pair_tokens->is('identifier') && !$pair_tokens->is('number') && !$pair_tokens->is('string')) {
				IssueList::add('error', "Map key must be an identifier, number or string.", $pair_tokens->consume());
				continue;
			}
			$key = $pair_tokens->consume();
			
			if (!$pair_tokens->is('symbol', ':')) {
				IssueList::add('error', "Map key needs to be followed by a colon ':' and an expression.", $pair_token->tryConsume(), $key);
				continue;
			}
			$colon = $pair_tokens->consume();
			
			if ($pair_tokens->isEmpty()) {
				IssueList::add('error', "Map key is missing its corresponding value expression after the colon ':'.", $key, $colon);
				continue;
			}
			$value = static::parseExpr($pair_tokens);
			if (!$value) continue;
			
			$pairs[] = new AST\Expr\InlineMapPair($key, $value);
		}
		return new AST\Expr\InlineMap($pairs, $group);
	}
}