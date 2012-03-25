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
			$d = $this->parseDef($ts);
			if ($d) $this->nodes[] = $d;
		}
	}
	
	private function parseDef(array &$ts)
	{
		if ($ts[0]->is('keyword')) return $this->parseKeywordDef(array_shift($ts), $ts);
		$t = array_shift($ts);
		$this->issues[] = new Issue(
			'warning',
			"Definition should start with a keyword.",
			$t->range
		);
		return null;
	}
	
	private function parseKeywordDef(Token &$keyword, array &$ts)
	{
		if ($keyword->text == 'import') return $this->parseImportDef($keyword, $ts);
		if ($keyword->text == 'func')   return $this->parseFuncDef($keyword, $ts);
		if ($keyword->text == 'type')   return $this->parseTypeDef($keyword, $ts);
		$this->issues[] = new Issue(
			'error',
			"Keyword '{$keyword->text}' has no meaning here.",
			$keyword->range
		);
		return null;
	}
	
	private function parseImportDef(Token &$keyword, array &$ts)
	{
		$name = array_shift($ts);
		if (!$name->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"Import requires a name.",
				$name->range,
				array($keyword->range)
			);
			return null;
		}
		if (count($ts) > 0 && $ts[0]->is('symbol', ';')) {
			array_shift($ts);
		}
		$name->context = 'import.name';
		
		return new AST\ImportStmt($keyword, $name);
		
		$i = new Node;
		$i->c_ignore = true;
		$i->kind  = 'def.import';
		$i->name  = $name;
		$i->range = clone $keyword->range;
		$i->range->combine($name->range);
		$name->node = $i;
		return $i;
	}
	
	private function parseFuncDef(Token &$keyword, array &$ts)
	{
		$name = array_shift($ts);
		if ($name->is('group', '()')) {
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
		if (!$name->is('identifier') && !$name->is('symbol')) {
			$this->issues[] = new Issue(
				'error',
				"function requires a name or operator symbol in paranthesis",
				$name->range,
				array($keyword->range)
			);
			return null;
		}
		
		if ($ts[0]->is('group', '()')) {
			$args_in = $this->parseFuncArgs(array_shift($ts)->tokens);
		}
		if (!isset($args_in)) {
			$args_in = array();
		}
		
		if ($ts[0]->is('symbol', '->') && $ts[1]->is('group', '()')) {
			array_shift($ts);
			$args_out = $this->parseFuncArgs(array_shift($ts)->tokens);
		}
		if (!isset($args_out)) {
			$args_out = array();
		}
		
		$body = array_shift($ts);
		if (!$body->is('group', '{}')) {
			$this->issues[] = new Issue(
				'error',
				"function requires a body",
				$body->range,
				array($keyword->range, $name->range)
			);
			return null;
		}
		$bodyNode = $this->parseBlock($body);
		
		$name->context = 'func.name';
		$body->context = 'func.body';
		
		return new AST\FuncStmt($keyword, $name, $args_in, $args_out, $bodyNode);
		
		/*$f = new Node;
		$f->kind  = 'def.func';
		$f->name  = $name;
		$f->in    = $args_in;
		$f->out   = $args_out;
		$f->body  = $bodyNode;
		$f->nodes = array($f->body);
		$f->nodes += $f->in;
		$f->nodes += $f->out;
		$name->node = $f;
		return $f;*/
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
			$args[] = $this->parseFuncArg($sub);
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
			/*$type = array_pop($ts);
			if (!$type->is('identifier')) {
				$this->issues[] = new Issue(
					'error',
					"Function argument requires a type.",
					$type->range
				);
				return null;
			}
			$type->context = 'def.func.arg.type';*/
			$type = $this->parseType($ts);
		}
		
		return new AST\FuncArg($type, $name);
	}
	
	private function parseTypeDef(Token $keyword, array &$ts)
	{
		//Type Name
		$name = array_shift($ts);
		if (!$name->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"type requires a name",
				$name->range,
				array($keyword->range)
			);
			return null;
		}
		$name->context = 'def.type.name';
		
		//Potential type attributes.
		/*$primitive = false;
		$attrs = array(
			'primitive' => false
		);
		while (count($ts) && $ts[0]->is('keyword')) {
			$attr = array_shift($ts);
			switch ($attr->text) {
				case 'primitive': $attrs['primitive'] = true; break;
				default: {
					$this->issues[] = new Issue(
						'warning',
						"'{$attr->text}' has no meaning as type attribute.",
						$attr->range,
						array($name->range)
					);
				} break;
			}
		}*/
		
		//Type Body
		$body = array_shift($ts);
		if (!$body->is('group', '{}')) {
			$this->issues[] = new Issue(
				'error',
				"type requires a definition block",
				$body->range,
				array($keyword->range, $name->range)
			);
			return null;
		}
		$body->context = 'def.type.body';
		
		$stmts = array();
		$dts = $body->tokens;
		while (count($dts)) {
			$stmt = $this->parseTypeStmt($dts);
			if ($stmt) $stmts[] = $stmt;
		}
		
		return new AST\TypeStmt($keyword, $name, $stmts);
		
		//Create the node.
		/*$t = new Node;
		$t->kind      = 'def.type';
		$t->name      = $name;
		$t->primitive = $primitive;
		$t->nodes     = array();
		$dts = $defs->tokens;
		while (count($dts)) {
			$s = $this->parseTypeStmt($dts);
			if ($s) $t->nodes[] = $s;
		}
		return $t;*/
	}
	
	private function parseTypeStmt(array &$ts)
	{
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
		if (count($sub) == 2 && $sub[1]->is('identifier')) {
			return $this->parseVarExpr($sub);
		}
		$range = null;
		foreach ($sub as $s) {
			if ($range) {
				$range->combine($s->range);
			} else {
				$range = clone $s->range;
			}
		}
		$this->issues[] = new Issue(
			'error',
			"Unknown statement in type definition.",
			$range
		);
		return null;
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
		switch ($keyword->text) {
			case 'if':     return $this->parseIfStmt    ($keyword, $ts); break;
			case 'else':   return $this->parseElseStmt  ($keyword, $ts); break;
			case 'for':    return $this->parseForStmt   ($keyword, $ts); break;
			case 'inline': return $this->parseInlineStmt($keyword, $ts); break;
		}
		/*if ($keyword->text == 'return') {
			$sub = array();
			while (count($ts)) {
				$t = array_shift($ts);
				if ($t->is('symbol', ';'))
					break;
				$sub[] = $t;
			}
			
			$r = new Node;
			$r->kind  = 'stmt.return';
			$r->expr  = $this->parseExpr($sub);
			$r->nodes = array($r->expr);
			return $r;
		}*/
		
		//Keyword meaningless.
		while (count($ts) && !array_shift($ts)->is('symbol', ';'));
		$this->issues[] = new Issue(
			'error',
			"Keyword '$keyword' has no meaning in a statement",
			$keyword->range
		);
		return null;
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
			return $this->parseTupleExpr($ts[0], $ts[0]->tokens);
		}
		
		if (count($ts) > 1) {
			foreach (Language::$unaryOperators as $ops) {
				if (in_array($ts[0]->text, $ops)) {
					return $this->parseUnOpExpr(array_shift($ts), $ts);
				}
			}
		}
		
		foreach (Language::$binaryOperators as $operators) {
			for ($i = 0; $i < count($ts); $i++) {
				if ($ts[$i]->is('symbol') && in_array($ts[$i]->text, $operators)) {
					return $this->parseBinOpExpr($ts[$i], array_slice($ts, 0, $i), array_slice($ts, $i+1));
				}
			}
		}
		
		if (count($ts) > 1 && $ts[count($ts)-1]->is('group', '()')) {
			return $this->parseCallExpr($ts);
		}
		if (count($ts) > 2 && $ts[count($ts)-2]->is('symbol', '.') && $ts[count($ts)-1]->is('identifier')) {
			return $this->parseMemberExpr($ts);
		}
		
		if (count($ts) == 2 && $ts[1]->is('identifier')) {
			return $this->parseVarExpr($ts);
		}
				
		$e = null;
		$range = clone $ts[0]->range;
		foreach ($ts as $t) {
			$range->combine($t->range);
		}
		
		if ($ts[0]->is('identifier')) {
			$e = $this->parseIdentExpr(array_shift($ts), $ts);
		}
		else if ($ts[0]->is('numeric')) {
			$e = new AST\ConstExpr('numeric', array_shift($ts));
			/*$e = new Node;
			$e->kind  = 'expr.const.numeric';
			$e->value = array_shift($ts);
			$e->range = $e->value->range;
			$e->value->node = $e;*/
		}
		else if ($ts[0]->is('string')) {
			$e = new AST\ConstExpr('string', array_shift($ts));
			/*$e = new Node;
			$e->kind  = 'expr.const.string';
			$e->value = array_shift($ts);
			$e->range = $e->value->range;
			$e->value->node = $e;*/
		}
		
		if ($e && count($ts) > 0) {
			$range = clone $ts[0]->range;
			foreach ($ts as $t) {
				$range->combine($t->range);
			}
			$this->issues[] = new Issue(
				'warning',
				"garbage in expression",
				$range,
				(isset($e->range) ? array($e->range) : null)
			);
		}
		return $e;
	}
	
	private function parseVarExpr(array $ts)
	{
		$name = array_pop($ts);
		$type = $this->parseType($ts);
		
		$name->context = 'expr.var.name';
		
		return new AST\VarExpr($type, $name);
		/*$v = new Node;
		$v->kind  = 'expr.var';
		$v->name  = $name;
		$v->type  = $type;
		$v->range = clone $name->range;
		$v->range->combine($type->range);
		$name->node = $v;
		return $v;*/
	}
	
	private function parseTupleExpr(Token &$grp, array $ts)
	{
		$exprs = array();
		while (count($ts)) {
			$sub = array();
			while (count($ts)) {
				$t = array_shift($ts);
				if ($t->is('symbol', ','))
					break;
				$sub[] = $t;
			}
			$exprs[] = $this->parseExpr($sub);
		}
		
		if (count($exprs) == 1) {
			return $exprs[0];
		}
		
		$t = new Node;
		$t->kind  = 'expr.tuple';
		$t->exprs = $exprs;
		$t->range = clone $grp->range;
		return $t;
	}
	
	private function parseUnOpExpr($operator, array &$ts)
	{
		$expr = $this->parseExpr($ts);
		
		$operator->context = 'expr.op.unary';
		
		if (!$expr) return null;
		return new AST\UnaryOpExpr($operator, $expr);
		
		/*$o = new Node;
		$o->kind  = 'expr.op.unary';
		$o->op    = $operator;
		$o->expr  = $this->parseExpr($ts);
		$o->range = $operator->range;
		$o->range->combine($o->expr->range);
		return $o;*/
	}
	
	private function parseBinOpExpr($operator, array &$lts, array &$rts)
	{
		$lhs = $this->parseExpr($lts);
		$rhs = $this->parseExpr($rts);
		
		$operator->context = 'expr.op.binary';
		
		if (!$lhs || !$rhs) return null;
		return new AST\BinaryOpExpr($operator, $lhs, $rhs);
		
		/*$o = new Node;
		$o->kind  = 'expr.op.binary';
		$o->op    = $operator;
		$o->lhs   = $this->parseExpr($lts);
		$o->rhs   = $this->parseExpr($rts);
		$o->range = clone $operator->range;
		if ($o->lhs) $o->range->combine($o->lhs->range);
		if ($o->rhs) $o->range->combine($o->rhs->range);
		return $o;*/
	}
	
	private function parseCallExpr(array &$ts)
	{
		$arg_group = array_pop($ts);
		$args = $this->parseCallArgs($arg_group->tokens);
		$expr = $this->parseExpr($ts);
		
		if (!$expr || !$args) return null;
		return new AST\CallExpr($expr, $arg_group, $args);
		
		/*$f = new Node;
		$f->kind   = 'expr.call';
		$f->args   = $this->parseCallArgs($arggrp->tokens);
		$f->callee = $this->parseExpr($ts);
		$f->callee->name->node = $f;
		$f->range  = clone $f->callee->range;
		$f->range->combine($arggrp->range);
		return $f;*/
	}
	
	private function parseCallArgs(array &$ts)
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
			$args[] = $this->parseCallArg($sub);
		}
		return $args;
	}
	
	private function parseCallArg(array &$ts)
	{
		$a = new Node;
		$a->kind  = 'expr.call.arg';
		$a->expr  = $this->parseExpr($ts);
		$a->range = clone $a->expr->range;
		return $a; 
	}
	
	private function parseMemberExpr(array &$ts)
	{
		$member = array_pop($ts);
		$dot    = array_pop($ts);
		$expr   = $this->parseExpr($ts);
		
		$member->context = 'expr.member';
		
		return new AST\MemberExpr($expr, $dot, $member);
		
		/*$m = new Node;
		$m->kind   = 'expr.member';
		$m->member = $member;
		$m->expr   = $this->parseExpr($ts);
		$m->range  = clone $member->range;
		$m->range->combine($m->expr->range);
		$member->node = $m;
		return $m;*/
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
			"Unable to parse expression starting with identifier '{$ident}'. Expected a variable name after '{$ident}'.",
			$range
		);
		return null;
	}
	
	private function parseType(array $ts)
	{
		if (count($ts) == 1) {
			if ($ts[0]->is('identifier')) {
				return new AST\IdentExpr(array_shift($ts));
				/*$n = new Node;
				$n->kind = ($ident->text[0] == '@' ? 'type.var' : 'type.name');
				$n->name = $ident;
				$n->range = clone $ident->range;
				$ident->node = $n;
				$ident->context = $n->kind;
				return $n;*/
			}
		}
		
		$range = clone $ts[0]->range;
		foreach ($ts as $t) {
			$range->combine($t->range);
		}
		$this->issues[] = new Issue(
			'error',
			"Unable to parse type.",
			$range
		);
		return null;
	}
}
