<?php

class Parser
{
	public $tokens;
	public $nodes;
	public $issues;
	
	public function run()
	{
		$this->nodes = array();
		$ts = $this->tokens;
		while (count($ts)) {
			$d = $this->parseStmt($ts);
			if ($d) $this->nodes[] = $d;
		}
	}
	
	static private function upToSymbol($symbol, array &$ts, $consumeSymbol = true)
	{
		$sub = array();
		while (count($ts)) {
			$t = array_shift($ts);
			if ($t->is('symbol', $symbol)) {
				if (!$consumeSymbol) array_unshift($ts, $t);
				break;
			}
			$sub[] = $t;
		}
		return $sub;
	}
	
	private function parseBlock(TokenGroup &$group)
	{
		$ts = $group->tokens;
		$stmts = array();
		while (count($ts)) {
			$stmt = $this->parseStmt($ts);
			if ($stmt) $stmts[] = $stmt;
		}
		return new AST\Block($group, $stmts);
	}
	
	private function parseBlockOrStmt(array &$ts)
	{
		if ($ts[0]->is('group', '{}')) {
			return $this->parseBlock(array_shift($ts));
		} else {
			return new AST\Block($this->parseStmt($ts));
		}
	}
	
	private function parseStmt(array &$ts)
	{
		if ($ts[0]->is('keyword')) return $this->parseKeywordStmt(array_shift($ts), $ts);
		$sub = array();
		while (count($ts)) {
			$t = array_shift($ts);
			if ($t->is('symbol', ';'))
				break;
			$sub[] = $t;
		}
		if (count($sub) == 0) {
			return null;
		}
		$expr = $this->parseExpr($sub);
		
		if (!$expr) return null;
		return new AST\ExprStmt($expr);
	}
	
	private function parseKeywordStmt(Token $keyword, array &$ts)
	{
		$func = 'parse'.ucwords($keyword->text).'Stmt';
		if (method_exists($this, $func)) {
			return $this->$func($keyword, $ts);
		}
		
		//Keyword meaningless.
		while (count($ts) && !array_shift($ts)->is('symbol', ';'));
		$this->issues[] = new Issue(
			'error',
			"Keyword '$keyword' has no meaning in a statement.",
			$keyword
		);
		return null;
	}
	
	private function parseImportStmt(Token &$keyword, array &$ts)
	{
		$name = null;
		if (count($ts) >= 1) $name = array_shift($ts);
		
		if (!$name->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"Import statement requires a file name.",
				$name,
				$keyword
			);
			return null;
		}
		if (count($ts) >= 1 && $ts[0]->is('symbol', ';')) array_shift($ts);
		
		if (!$name) return null;
		return new AST\ImportStmt($keyword, $name);
	}
	
	private function parseFuncStmt(Token &$keyword, array &$ts)
	{
		$name = null;
		if (count($ts) >= 1) $name = array_shift($ts);
		
		if ($name && $name->is('group', '()')) {
			$tokens = $name->tokens;
			if (count($tokens) < 1) {
				$this->issues[] = new Issue(
					'error',
					"Function requires operator symbol inside paranthesis.",
					$name->range,
					array($keyword->range)
				);
				return null;
			}
			$name = array_shift($tokens);
			if (count($tokens)) {
				$this->issues[] = new Issue(
					'warning',
					"Function definition should have only one operator symbol in paranthesis. Ignoring additional tokens.",
					array_reduce(array_map(function($t){ return $t->range; }, $tokens), function($a,$b) { if (!$a) return $b; $r = clone $a; $r->combine($b); return $r; }),
					array($name->range)
				);
			}
		}
		if (!$name || (!$name->is('identifier') && !$name->is('symbol'))) {
			$this->issues[] = new Issue(
				'error',
				"Function requires a name or an operator symbol in paranthesis.",
				$name,
				$keyword
			);
			return null;
		}
		
		$args_in = $this->parseFuncArgsIn($ts);
		
		$bodyNode = null;
		$args_out = null;
		if (count($ts) >= 1 && $ts[0]->is('symbol', '=')) {
			$eq = array_shift($ts);
			$sub = $this->upToSymbol(';', $ts);
			if (!count($sub)) {
				$this->issues[] = new Issue(
					'error',
					"Function requires an expression after '='.",
					$eq,
					array($keyword, $name)
				);
				return null;
			}
			$bodyNode = $this->parseExpr($sub);
			$args_out = array();
		} else {
			$args_out = $this->parseFuncArgsOut($ts);
			
			$body = null;
			if (count($ts) && $ts[0]->is('group', '{}')) $body = array_shift($ts);
			
			if (!$body) {
				$this->issues[] = new Issue(
					'error',
					"Function requires a body.",
					$body,
					array($keyword, $name)
				);
				return null;
			}
			$bodyNode = $this->parseBlock($body);
		}
		
		if (!$name || $args_in === null || $args_out === null || !$bodyNode) return null;
		return new AST\FuncStmt($keyword, $name, $args_in, $args_out, $bodyNode);
	}
	
	private function parseFuncArgsIn(array &$ts)
	{
		if (count($ts) >= 1 && $ts[0]->is('group', '()')) {
			return $this->parseFuncArgs(array_shift($ts)->tokens);
		} else {
			return array();
		}
	}
	
	private function parseFuncArgsOut(array &$ts)
	{
		if (count($ts) >= 2 && $ts[0]->is('symbol', '->') && $ts[1]->is('group', '()')) {
			array_shift($ts);
			return $this->parseFuncArgs(array_shift($ts)->tokens);
		} else {
			return array();
		}
	}
	
	private function parseFuncArgs(array &$ts)
	{
		$args = array();
		while (count($ts)) {
			$sub = array();
			while (count($ts)) {
				$t = array_shift($ts);
				if ($t->is('symbol', ','))
					break;
				$sub[] = $t;
			}
			$arg = $this->parseFuncArg($sub);
			if (!$arg) return null;
			$args[] = $arg;
		}
		return $args;
	}
	
	private function parseFuncArg($ts)
	{
		$name = array_pop($ts);
		if (!$name->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"Function argument requires a name.",
				$name->range
			);
			return null;
		}
		
		$type = null;
		if (count($ts) > 0) {
			$type = $this->parseExpr($ts);
		}
		
		if (!$name) return null;
		return new AST\FuncArg($type, $name);
	}
	
	private function parseTypeStmt(Token $keyword, array &$ts)
	{
		if (count($ts) < 2) {
			$this->issues[] = new Issue(
				'error',
				"Type requires at least a name and a body.",
				$ts,
				$keyword
			);
			return null;
		}
		
		//Type Name
		$name = array_shift($ts);
		if (!$name->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"Type requires a name.",
				$name,
				$keyword
			);
			return null;
		}
		
		//Parent Type
		$parent = null;
		if ($ts[0]->is('symbol', ':')) {
			$col = array_shift($ts);
			if ($ts[0]->is('identifier')) {
				$parent = new AST\IdentExpr(array_shift($ts));
			} else {
				$this->issues[] = new Issue(
					'error',
					"Type {$name} requires a parent type name after ':'.",
					$name,
					$col
				);
				return null;
			}
		}
		
		//Type Body
		if (!count($ts) || !$ts[0]->is('group', '{}')) {
			$this->issues[] = new Issue(
				'error',
				"Type {$name} requires a body.",
				$name,
				(count($ts) ? $ts[0] : null)
			);
			return null;
		}
		$body = array_shift($ts);
		$bodyNode = $this->parseBlock($body);
		
		if (!$name || !$bodyNode) return null;
		return new AST\TypeStmt($keyword, $name, $parent, $bodyNode);
	}
	
	private function parseIfStmt(Token $keyword, array &$ts)
	{
		if (count($ts) < 2) {
			$this->issues[] = new Issue(
				'error',
				"'if' requires a condition and a body.",
				$keyword->range
			);
			return null;
		}
		
		$condition_group = array_shift($ts);
		if (!$condition_group->is('group', '()')) {
			$this->issues[] = new Issue(
				'error',
				"'if' requires a condition within paranthesis.",
				$condition_group->range,
				array($keyword->range)
			);
			return null;
		}
		$condition = $this->parseExpr($condition->tokens);
		
		$body = $this->parseBlockOrStmt($ts);
		
		$else = null;
		if (count($ts) > 0 && $ts[0]->is('keyword', 'else')) {
			$else = $this->parseKeywordStmt(array_shift($ts), $ts);
		}
		
		if (!$condition || !$body) return null;
		return new AST\IfStmt($keyword, $condition, $body, $else);
	}
	
	private function parseElseStmt(Token $keyword, array &$ts)
	{
		if (count($ts) < 1) {
			$this->issues[] = new Issue(
				'error',
				"'else' requires a body.",
				$keyword->range
			);
			return null;
		}
		$body  = $this->parseBlockOrStmt($ts);
		
		if (!$body) return null;
		return new AST\ElseStmt($keyword, $body);
	}
	
	private function parseForStmt(Token $keyword, array &$ts)
	{
		if (count($ts) < 2) {
			$this->issues[] = new Issue(
				'error',
				"'for' requries a loop configuration and a body.",
				$keyword->range
			);
			return null;
		}
		
		$group = array_shift($ts);
		if (!$group->is('group', '()')) {
			$this->issues[] = new Issue(
				'error',
				"'for' requires initial statement, condition expression and step statement in paranthesis.",
				$group->range,
				array($keyword->range)
			);
			return null;
		}
		
		$initial   = null;
		$condition = null;
		$step      = null;
		$sts = $grp->tokens;
		for ($i = 0; i < 3 && count($sts); $i++) {
			$sub = array();
			while (count($sts)) {
				$t = array_shift($sts);
				if ($t->is('symbol', ';'))
					break;
				$sub[] = $t;
			}
			if ($i == 0) $initial   = $this->parseStmt($sub);
			if ($i == 1) $condition = $this->parseExpr($sub);
			if ($i == 2) $step      = $this->parseStmt($sub);
		}
		
		$body = $this->parseBlockOrStmt($ts);
		
		if (!$initial || !$condition || !$step || !$body) return null;
		return new AST\ForStmt($keyword, $group, $initial, $condition, $step, $body);
	}
	
	private function parseInlineStmt(Token $keyword, array &$ts)
	{
		if (count($ts) < 1 || !$ts[0]->is('group', '{}')) {
			$this->issues[] = new Issue(
				'error',
				"'inline' requires a body containing C code.",
				$ts[0]->range,
				array($keyword->range)
			);
			return null;
		}
		$body = array_shift($ts);
		
		$range = $gbody->range;
		$txt = substr($range->source->content, $range->start->offset + 1, $range->end->offset - $range->start->offset - 2);
		
		$txt = trim($txt);
		preg_match('/^(\s+)/m', $txt, $matches);
		$txt = str_replace("\n$matches[0]", "\n", $txt);
		
		return new AST\InlineStmt($keyword, $body, $txt);
	}
	
	private function parseExpr(array $ts)
	{
		if (count($ts) == 1 && $ts[0]->is('group', '()')) {
			return $this->parseTupleExpr($ts[0]->tokens);
		}
		
		if (count($ts) >= 2) {
			foreach (Language::$unaryOperators as $ops) {
				if (in_array($ts[0]->text, $ops)) {
					return $this->parseUnOpExpr(array_shift($ts), $ts);
				}
			}
		}
		
		if (count($ts) >= 3) {
			if ($ts[0]->is('symbol', "'") && $ts[count($ts)-1]->is('symbol', "'")) {
				$ap1 = array_shift($ts);
				$ap2 = array_pop($ts);
				return new AST\NativeTypeExpr($ts);
			}
			
			foreach (Language::$binaryOperators as $operators) {
				for ($i = 0; $i < count($ts); $i++) {
					if ($ts[$i]->is('symbol') && in_array($ts[$i]->text, $operators)) {
						return $this->parseBinOpExpr($ts[$i], array_slice($ts, 0, $i), array_slice($ts, $i+1));
					}
				}
			}
		}
		
		if (count($ts) > 1 && $ts[count($ts)-1]->is('group', '()')) {
			return $this->parseCallExpr($ts);
		}
		if (count($ts) > 2 && $ts[count($ts)-2]->is('symbol', '.') && $ts[count($ts)-1]->is('identifier')) {
			return $this->parseMemberExpr($ts);
		}
		
		if (count($ts) == 1) {
			if ($ts[0]->is('identifier')) return new AST\IdentExpr(array_shift($ts));
			if ($ts[0]->is('numeric'))    return new AST\ConstExpr('numeric', array_shift($ts));
			if ($ts[0]->is('string'))     return new AST\ConstExpr('string', array_shift($ts));
		}
		
		$this->issues[] = new Issue(
			'error',
			"Unable to parse expression.",
			$ts
		);
		return null;
	}
	
	private function parseVarStmt(Token $keyword, array &$ts)
	{
		$sub = static::upToSymbol(';', $ts);
		if (count($sub) < 1) {
			$this->issues[] = new Issue(
				'error',
				"Variable Definition requires at least a name.",
				$sub,
				$keyword
			);
			return null;
		}
		
		$def = static::upToSymbol('=', $sub, false);
		$name = array_pop($def);
		
		$type = null;
		if (count($def)) $type = $this->parseExpr($def);
		
		$initial = null;
		if (count($sub) > 0) {
			$eq = array_shift($sub);
			if (count($sub) == 0 || !$eq->is('symbol', '=')) {
				$this->issues[] = new Issue(
					'error',
					"Variable Definition with initial value needs to be followed by '=' and an expression.",
					$sub,
					array($type, $name)
				);
				return null;
			}
			$initial = $this->parseExpr($sub);
		}
		
		if (!$name) return null;
		return new AST\VarStmt($keyword, $type, $name, $initial);
	}
	
	private function parseTupleExpr(array $ts)
	{
		$exprs = array();
		while (count($ts)) {
			$sub  = static::upToSymbol(',', $ts);
			
			$name = null;
			if (count($sub) > 2 && $sub[1]->is('symbol', ':')) {
				$name = array_shift($sub);
				$col  = array_shift($sub);
				if (!$name->is('identifier')) {
					$this->issues[] = new Issue(
						'error',
						"Tuple field name has to be an identifier.",
						$name
					);
					return null;
				}
				$name = $name->text;
			}
			
			$expr = $this->parseExpr($sub);
			
			if ($expr) {
				if ($name) {
					$exprs[$name] = $expr;
				} else {
					$exprs[] = $expr;
				}
			}
		}
		
		//Resolve tuples with only one unnamed field immediately.
		if (count($exprs) == 1 && isset($exprs[0])) return $exprs[0];
		
		return new AST\TupleExpr($exprs);
	}
	
	private function parseUnOpExpr($operator, array &$ts)
	{
		$expr = $this->parseExpr($ts);
		
		if (!$expr) return null;
		return new AST\UnaryOpExpr($operator, $expr);
	}
	
	private function parseBinOpExpr($operator, array &$lts, array &$rts)
	{
		$lhs = $this->parseExpr($lts);
		$rhs = $this->parseExpr($rts);
		
		if (!$lhs || !$rhs) return null;
		return new AST\BinaryOpExpr($operator, $lhs, $rhs);
	}
	
	private function parseCallExpr(array &$ts)
	{
		$arg_group = array_pop($ts);
		$args = $this->parseCallArgs($arg_group->tokens);
		$expr = $this->parseExpr($ts);
		
		if (!$expr || $args === null) return null;
		return new AST\CallExpr($expr, $args);
	}
	
	private function parseCallArgs(array &$ts)
	{
		$args = array();
		while (count($ts)) {
			$sub = static::upToSymbol(',', $ts);
			$args[] = $this->parseCallArg($sub);
		}
		return $args;
	}
	
	private function parseCallArg(array &$ts)
	{
		$name = null;
		if (count($ts) >= 2 && $ts[1]->is('symbol', ':')) {
			$name = array_shift($ts);
		}
		$expr = $this->parseExpr($ts);
		
		if (!$expr) return null;
		return new AST\CallArg($name, $expr);
	}
	
	private function parseMemberExpr(array &$ts)
	{
		$name = array_pop($ts);
		$dot  = array_pop($ts);
		$expr = $this->parseExpr($ts);
		
		if (!$expr) return null;
		return new AST\MemberExpr($expr, $name);
	}
	
	private function parseIdentExpr($ident, array &$ts)
	{
		if (!count($ts)) {
			$ident->context = 'expr.ident';
			return new AST\IdentExpr($ident);
			
			/*$i = new Node;
			$i->kind  = 'expr.ident';
			$i->name  = $ident;
			$i->range = clone $ident->range;
			$ident->node = $i;
			return $i;*/
		}
		if ($ts[0]->is('identifier')) {
		}
		$range = clone $ident->range;
		foreach ($ts as $t) {
			$range->combine($t->range);
		}
		$this->issues[] = new Issue(
			'error',
			"Unable to parse expression starting with identifier '{$ident}'.",
			$range
		);
		return null;
	}
	
	private function parseType(array &$ts)
	{
		if (count($ts) == 0) return null;
		
		$token = array_shift($ts);
		if ($token->is('identifier')) {
			return new AST\IdentExpr($token);
		}
		
		$this->issues[] = new Issue(
			'error',
			"Unable to parse type.",
			$token
		);
		return null;
	}
	
	private function parseReturnStmt(Token $keyword, array &$ts)
	{
		$sub = static::upToSymbol(';', $ts);
		
		$expr = null;
		if (count($sub)) $expr = $this->parseTupleExpr($sub);
		
		return new AST\ReturnStmt($keyword, $expr);
	}
	
	private function parseNativeStmt(Token $keyword, array &$ts)
	{
		if (!$ts[0]->is('keyword', 'func')) {
			$this->issues[] = new Issue(
				'error',
				"'native' keyword needs to be followed by a function declaration.",
				$keyword,
				$ts[0]
			);
			return null;
		}
		$func = array_shift($ts);
		
		if (count($ts) < 1 || !$ts[0]->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"Native function requires a name.",
				array($keyword, $func)
			);
			return null;
		}
		$name = array_shift($ts);
		
		$ins  = $this->parseFuncArgsIn($ts);
		$outs = $this->parseFuncArgsOut($ts);
		
		if (count($ts) < 1 || !$ts[0]->is('symbol', ';')) {
			$this->issues[] = new Issue(
				'warning',
				"Native function declaration needs to be terminated by a ';'.",
				$name,
				array($keyword, $func)
			);
		}
		return new AST\NativeFuncStmt($keyword, $name, $ins, $outs);
	}
}