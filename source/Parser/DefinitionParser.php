<?php
namespace Parser;
use AST;
use Lexer\Token;
use Lexer\TokenGroup;
use Lexer\TokenList;
use IssueList;
use Language;

class DefinitionParser
{
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
		if ($tokens->consumeIf('symbol', '->') && $tokens->is('group', '()'))
			$args_out = static::parseFuncArgs($tokens->consume()->getStrippedTokens());
		else
			$args_out = array();
		
		//Extract the body.
		$body = null;
		if ($tokens->is('group', '{}')) {
			$body = StatementParser::parseBlock($tokens->consume());
		}
		else {
			IssueList::add('error', "Function requires a body.", array($keyword, $name));
			goto body_failed;
		}
		body_failed:
		
		if (!$name || $args_in === null || $args_out === null || !$body) return null;
		return new AST\Stmt\FuncDef($keyword, $name, $args_in, $args_out, $body);
	}
	
	static public function parseFuncArgs(TokenList $tokens)
	{
		$args = array();
		while (!$tokens->isEmpty()) {
			$arg_tokens = $tokens->upTo('symbol', ',');
			$comma = $tokens->consumeIf('symbol', ',');
			if ($arg_tokens->isEmpty()) {
				IssueList::add('warning', "Ignoring gratuitous comma. Mabye you forgot to type a function argument?", $comma);
				continue;
			}
			$arg = static::parseFuncArg($arg_tokens);
			if ($arg) $args[] = $arg;
		}
		return $args;
	}
	
	static public function parseFuncArg(TokenList $tokens)
	{
		if (!$tokens->backIs('identifier')) {
			IssueList::add('error', "Function argument requires a name.", $tokens->getTokens());
			return null;
		}
		$name = $tokens->backConsume();
		
		$type = null;
		if (!$tokens->isEmpty()) {
			$type = ExpressionParser::parseExpr($tokens);
			if (!$type) return null;
		}
		
		return new AST\Stmt\FuncArg($type, $name);
	}
}