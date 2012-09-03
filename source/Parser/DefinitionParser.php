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
		else if ($tokens->is('backtick')) {
			$b = $tokens->consume();
			$symbol = $b->getText();
			if (!$symbol) {
				IssueList::add('error', "Operator function requires an operator symbol inside backticks (`<op>`).", $b);
				goto name_failed;
			}
			if (!in_array($symbol, Language::$operators)) {
				$symbols = implode("  ", Language::$operators);
				IssueList::add('error', "Name of operator function '$symbol' is not an operator. Valid operators are:\n$symbols", $b);
				goto name_failed;
			}
			$name = $b;
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
	
	
	
	static public function parseTypeDefStmt(Token $keyword, TokenList $tokens)
	{
		$name = null;
		if ($tokens->is('identifier')) {
			$name = $tokens->consume();
		} else {
			IssueList::add('error', "Type requires a name after '{$keyword->getText()}'.", $keyword);
		}
		
		//Extract the supertype.
		if ($tokens->consumeIf('symbol', ':') && $tokens->is('identifier')) {
			$super = $tokens->consume();
		} else {
			$super = null;
		}
		
		//Extract the body.
		$body = null;
		if ($tokens->is('group', '{}')) {
			$body = static::parseTypeBody($tokens->consume());
		}
		else {
			IssueList::add('error', "Type requires a body.", array($keyword, $name));
		}
		
		if (!$name || !$body) return null;
		return new AST\Stmt\TypeDef($keyword, $name, $super, $body);
	}
	
	static public function parseTypeBody(TokenGroup $group)
	{
		$tokens = $group->getStrippedTokens();
		$stmts = array();
		while (!$tokens->isEmpty()) {
			$stmt = static::parseTypeBodyStmt($tokens);
			if ($stmt) $stmts[] = $stmt;
		}
		return new AST\Block($stmts, $group);
	}
	
	static public function parseTypeBodyStmt(TokenList $tokens)
	{
		if ($keyword = $tokens->consumeIf('identifier', 'func'))
			return static::parseFuncDefStmt($keyword, $tokens);
		if ($keyword = $tokens->consumeIf('identifier', 'type'))
			return static::parseTypeDefStmt($keyword, $tokens);
		if ($tokens->is('identifier', 'var'))
			return StatementParser::parseStmt($tokens);
		
		$ignored = $tokens->upTo('symbol', ';');
		$tokens->consumeIf('symbol', ';');
		IssueList::add('error', "Only function, type and member definitions allowed inside type body.", $ignored->getTokens());
		return null;
	}
}