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
		if ($tokens->is('identifier') && in_array($tokens->getText(), Language::$expressionKeywords)) {
			return static::parseKeywordExpr($tokens->consume(), $tokens);
		}
		
		if ($tokens->count() >= 3) {
			if ($tokens->backIs('symbol', '.', 1)) return static::parseMemberAccessExpr($tokens->backConsume(), $tokens->backConsume(), $tokens);
			
			//Binary Operators.
			foreach (Language::$binaryOperators as $operators) {
				for ($i = 0; $i < $tokens->count(); $i++) {
					if ($tokens->is('symbol', null, $i) && in_array($tokens->getText($i), $operators)) {
						$lhs = $tokens->upTo('symbol', $tokens->getText($i));
						$op  = $tokens->consume();
						$rhs = $tokens;
						return static::parseBinaryOperator($lhs, $op, $rhs);
					}
				}
			}
		}
		
		if ($tokens->count() >= 2) {
			if ($tokens->backIs('group', '()')) return static::parseCallExpr($tokens->backConsume(), $tokens);
		}
		
		if ($tokens->count() == 1) {
			if ($tokens->is('identifier')) return new AST\Expr\Identifier($tokens->consume());
			if ($tokens->is('number') || $tokens->is('string')) return new AST\Expr\Constant($tokens->consume());
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
	
	static public function parseKeywordExpr(Token $keyword, TokenList $tokens)
	{
		//Try to call the parse<keyword>Expr function if one exists.
		$name = "parse".ucfirst($keyword->getText())."Expr";
		if (method_exists(__CLASS__, $name)) {
			return call_user_func(array(__CLASS__, $name), $keyword, $tokens);
		}
		
		//We don't know what to do with this keyword, so throw an error.
		IssueList::add('error', "Keyword '{$keyword->getText()}' cannot be used in an expression.", $keyword, $tokens->getTokens());
		return null;
	}
	
	static public function parseVarExpr(Token $keyword, TokenList $tokens)
	{
		if ($tokens->isEmpty()) {
			IssueList::add('warning', "Ignoring gratuitous keyword '{$keyword->getText()}'.", $keyword);
			return null;
		}
		
		//Separate the variable at the '=' (or the end of the token list).
		$var_tokens = $tokens->upTo('symbol', '=');
		if ($var_tokens->isEmpty()) {
			IssueList::add('error', "Variable needs at least a name before '='.", $keyword, $stmt_tokens->tryConsume());
			return null;
		}
		
		//Extract name.
		$name = $var_tokens->backConsume();
		if (!$name->is('identifier')) {
			IssueList::add('error', "Variable needs an identifier as name, got {$name->getNice()} instead.", $name, $keyword);
			return null;
		}
		
		//Extract type (optional).
		$type = null;
		if (!$var_tokens->isEmpty()) {
			$type = ExpressionParser::parseExpr($var_tokens);
			if (!$type) return null;
		}
		
		//Extract initial value (optional).
		$initial = null;
		if ($assign = $tokens->consumeIf('symbol', '=')) {
			if ($tokens->isEmpty()) {
				IssueList::add('error', "Variable needs either an initial expression after '=', or no '=' at all.", $assign, array($keyword, $name));
				return null;
			}
			$initial = ExpressionParser::parseExpr($tokens);
			if (!$initial) return null;
		}
		
		return new AST\Expr\VarDef($keyword, $type, $name, $initial);
	}
	
	static public function parseNewExpr(Token $keyword, TokenList $tokens)
	{
		//Parse the type expression.
		$expr = static::parseExpr($tokens);
		if (!$expr) return null;
		
		return new AST\Expr\NewOp($keyword, $expr);
	}
	
	static public function parseCallExpr(TokenGroup $args_group, TokenList $tokens)
	{
		//Parse the callee.
		$callee = static::parseExpr($tokens);
		if (!$callee) return null;
		
		//Parse the arguments.
		$args = array();
		$args_tokens = $args_group->getStrippedTokens();
		while (!$args_tokens->isEmpty()) {
			$arg_tokens = $args_tokens->upTo('symbol', ',');
			$comma = $args_tokens->consumeIf('symbol', ',');
			if ($arg_tokens->isEmpty()) {
				IssueList::add('warning', "Ignoring gratuitous comma. Maybe you forgot to type a call argument?", $comma);
				continue;
			}
			
			$name = null;
			$colon = null;
			if ($arg_tokens->is('symbol', ':', 1)) {
				$name = $arg_tokens->consume();
				$colon = $arg_tokens->consume();
				if (!$name->is('identifier')) {
					IssueList::add('error', "Call argument needs an identifier as name, got {$name->getNice()} instead.", $name, $arg_tokens->getTokens());
					continue;
				}
			}
			
			if ($arg_tokens->isEmpty()) {
				IssueList::add('error', "Call argument needs an expression after the name and ':'.", array($name, $colon));
				continue;
			}
			$expr = static::parseExpr($arg_tokens);
			if (!$expr) continue;
			
			$args[] = new AST\Expr\CallArg($expr, $name);
		}
		
		return new AST\Expr\Call($callee, $args);
	}
	
	static public function parseMemberAccessExpr(Token $name, Token $period, TokenList $tokens)
	{
		$expr = static::parseExpr($tokens);
		if (!$expr) return null;
		return new AST\Expr\MemberAccess($expr, $name);
	}
	
	static public function parseBinaryOperator(TokenList $lhs, Token $operator, TokenList $rhs)
	{
		//Parse the left and right hand side.
		$lhs_expr = static::parseExpr($lhs);
		$rhs_expr = static::parseExpr($rhs);
		if (!$lhs_expr || !$rhs_expr) return null;
		
		//Wrap up.
		return new AST\Expr\Operator\Binary($lhs_expr, $operator, $rhs_expr);
	}
}