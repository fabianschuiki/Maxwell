<?php

class Parser
{
	public $tokens;
	public $nodes;
	public $issues;
	
	public function run()
	{
		$this->nodes = array();
		$this->issues = array();
		$ts = $this->tokens;
		while (count($ts)) {
			$d = $this->parseDef($ts);
			if ($d) $this->nodes[] = $d;
		}
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
	}
	
	private function parseDef(array &$ts)
	{
		if ($ts[0]->is('keyword')) return $this->parseKeywordDef(array_shift($ts), $ts);
		$t = array_shift($ts);
		$this->issues[] = new Issue(
			'warning',
			"definition should start with a keyword",
			$t->range
		);
		return null;
	}
	
	private function parseKeywordDef(Token &$keyword, array &$ts)
	{
		if ($keyword->text == 'func') return $this->parseFuncDef($keyword, $ts);
		if ($keyword->text == 'type') return $this->parseTypeDef($keyword, $ts);
		$this->issues[] = new Issue(
			'error',
			"keyword '{$keyword->text}' has no meaning here",
			$keyword->range
		);
		return null;
	}
	
	private function parseFuncDef(Token &$keyword, array &$ts)
	{
		$name = array_shift($ts);
		if (!$name->is('identifier')) {
			$this->issues[] = new Issue(
				'error',
				"function requires a name",
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
		
		$name->context = 'func.name';
		$body->context = 'func.body';
		
		$f = new Node;
		$f->kind  = 'def.func';
		$f->name  = $name;
		$f->in    = $args_in;
		$f->out   = $args_out;
		$f->body  = $this->parseBlock($body);
		$f->nodes = array($f->body);
		$f->nodes += $f->in;
		$f->nodes += $f->out;
		return $f;
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
			$this->issues[] = "{$name->range}: function argument name required, $name found";
			return null;
		}
		
		$type = null;
		if (count($ts) > 0) {
			$type = array_pop($ts);
			if (!$type->is('identifier')) {
				$this->issues[] = "{$type->range}: function argument type should be an identifier, $type found";
				return null;
			}
			$type->context = 'def.func.arg.type';
		}
		
		$a = new Node;
		$a->kind  = 'def.func.arg';
		$a->name  = $name;
		$a->type  = $type;
		return $a;
	}
	
	private function parseTypeDef(Token &$keyword, array &$ts)
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
		$name->context = 'type.name';
		
		//Type Definition
		$defs = array_shift($ts);
		if (!$defs->is('group', '{}')) {
			$this->issues[] = new Issue(
				'error',
				"type requires a definition block",
				$defs->range,
				array($keyword->range, $name->range)
			);
			return null;
		}
		$defs->context = 'type.defs';
		
		//Create the node.
		$t = new Node;
		$t->kind  = 'def.type';
		$t->name  = $name;
		/*$dts = $defs->tokens;
		while (count($dts)) {
			$d = $this->parseDef($dts);
			if ($d) $t->nodes[] = $d;
		}*/
		return $t;
	}
	
	private function parseBlock(TokenGroup &$grp)
	{
		$b = new Node;
		$b->kind  = 'stmt.block';
		$b->group = $grp;
		$b->range = $grp->range;
		$b->nodes = array();
		$ts = $grp->tokens;
		while (count($ts)) {
			$s = $this->parseStmt($ts);
			if ($s)	$b->nodes[] = $s;
		}
		return $b;
	}
	
	private function parseBlockOrStmt(array &$ts)
	{
		if ($ts[0]->is('group', '{}')) {
			return $this->parseBlock(array_shift($ts));
		} else {
			$s = $this->parseStmt($ts);
			$b = new Node;
			$b->kind = 'stmt.block';
			$b->nodes = array();
			if ($s) $b->nodes[] = &$s;
			return $b;
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
		return $this->parseExpr($sub);
	}
	
	private function parseKeywordStmt($keyword, array &$ts)
	{
		if ($keyword->text == 'if') {
			if (!$ts[0]->is('group', '()')) {
				$this->issues[] = "{$ts[0]->range}: if requires a condition within paranthesis, {$ts[0]} found";
				return null;
			}
			$condition = array_shift($ts);
			
			$block = $this->parseBlockOrStmt($ts);
			
			if (count($ts) > 0 && $ts[0]->is('keyword', 'else')) {
				$else = $this->parseKeywordStmt(array_shift($ts), $ts);
			} else {
				$else = null;
			}
			
			$i = new Node;
			$i->kind      = 'stmt.if';
			$i->condition = $this->parseExpr($condition->tokens);
			$i->body      = $block;
			$i->else      = $else;
			$i->range     = clone $keyword->range;
			$i->range->combine($block->range);
			if ($else) $i->range->combine($block->else->range);
			return $i;
		}
		if ($keyword->text == 'else') {
			$e = new Node;
			$e->kind  = 'stmt.else';
			$e->body  = $this->parseBlockOrStmt($ts);
			return $e;
		}
		if ($keyword->text == 'for') {
			if (!$ts[0]->is('group', '()')) {
				$this->issues[] = "{$ts[0]->range}: for loop requires initial statement, condition and step statement in paranthesis, {$ts[0]} found";
				return null;
			}
			$grp = array_shift($ts);
			
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
			
			$f = new Node;
			$f->kind      = 'stmt.for';
			$f->initial   = $initial;
			$f->condition = $condition;
			$f->step      = $step;
			$f->body      = $this->parseBlockOrStmt($ts);
			return $f;
		}
		if ($keyword->text == 'return') {
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
		}
		
		//Keyword meaningless.
		while (count($ts) && !array_shift($ts)->is('symbol', ';'));
		$this->issues[] = new Issue(
			'error',
			"keyword '{$keyword->text}' has no meaning in a statement",
			$keyword->range
		);
		return null;
	}
	
	private function parseExpr(array $ts)
	{
		if (count($ts) == 1 && $ts[0]->is('group', '()')) {
			return $this->parseExpr($ts[0]->tokens);
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
		
		if (count($ts) > 1 && $ts[count($ts)-1]->is('group', '()')) return $this->parseCallExpr($ts);
		if (count($ts) > 2 && $ts[count($ts)-2]->is('symbol', '.') && $ts[count($ts)-1]->is('identifier')) return $this->parseMemberExpr($ts);
				
		$e = null;
		if ($ts[0]->is('identifier')) $e = $this->parseIdentExpr(array_shift($ts), $ts);
		else if ($ts[0]->is('numeric')) {
			$e = new Node;
			$e->kind  = 'expr.const.numeric';
			$e->value = array_shift($ts);
			$e->range = $e->value->range;
		}
		else if ($ts[0]->is('string')) {
			$e = new Node;
			$e->kind  = 'expr.const.string';
			$e->value = array_shift($ts);
			$e->range = $e->value->range;
		}
		if (count($ts) > 0) {
			$range = $ts[0]->range;
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
	
	private function parseUnOpExpr($operator, array &$ts)
	{
		$operator->context = 'expr.op.unary';
		
		$o = new Node;
		$o->kind  = 'expr.op.unary';
		$o->op    = $operator;
		$o->expr  = $this->parseExpr($ts);
		$o->range = $operator->range;
		$o->range->combine($o->expr->range);
		return $o;
	}
	
	private function parseBinOpExpr($operator, array &$lts, array &$rts)
	{
		$operator->context = 'expr.op.binary';
		
		$o = new Node;
		$o->kind  = 'expr.op.binary';
		$o->op    = $operator;
		$o->lhs   = $this->parseExpr($lts);
		$o->rhs   = $this->parseExpr($rts);
		$o->range = clone $operator->range;
		$o->range->combine($o->lhs->range);
		$o->range->combine($o->rhs->range);
		return $o;
	}
	
	private function parseCallExpr(array &$ts)
	{
		$f = new Node;
		$f->kind   = 'expr.call';
		$f->args   = $this->parseCallArgs(array_pop($ts)->tokens);
		$f->callee = $this->parseExpr($ts);
		$f->nodes  = array_merge(array($f->callee), $f->args);
		return $f;
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
		$a->nodes = array($a->expr);
		return $a; 
	}
	
	private function parseMemberExpr(array &$ts)
	{
		$member = array_pop($ts);
		array_pop($ts); //dot operator
		
		$member->context = 'expr.member';
		
		$m = new Node;
		$m->kind   = 'expr.member';
		$m->member = $member;
		$m->expr   = $this->parseExpr($ts);
		$m->nodes  = array($m->expr);
		return $m;
	}
	
	private function parseIdentExpr($ident, array &$ts)
	{
		if (!count($ts)) {
			$ident->context = 'expr.ident';
			
			$i = new Node;
			$i->kind  = 'expr.ident';
			$i->name  = $ident->text;
			$i->token = $ident;
			$i->range = clone $ident->range;
			return $i;
		}
		if ($ts[0]->is('identifier')) {
			$type = $ident;
			$name = array_shift($ts);
			
			$name->context = 'expr.var.name';
			$type->context = 'expr.var.type';
			
			$v = new Node;
			$v->kind  = 'expr.var';
			$v->name  = $name;
			$v->type  = $type;
			$v->range = clone $name->range;
			$v->range->combine($type->range);
			return $v;
		}
		return null;
	}
}
