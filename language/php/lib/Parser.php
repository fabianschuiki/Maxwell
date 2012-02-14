<?php

class Parser
{
	static public $operators = array(
		array('=', ':='),
		array('==', '!='),
		array('+', '-'),
		array('*', '/'),
	);
	
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
		$this->issues[] = "{$t->range}: garbage $t";
		return null;
	}
	
	private function parseKeywordDef(Token &$keyword, array &$ts)
	{
		if ($keyword->text == 'func') return $this->parseFuncDef($ts);
		$this->issues[] = "{$keyword->range}: keyword {$keyword->text} has no meaning here";
		return null;
	}
	
	private function parseFuncDef(array &$ts)
	{
		$name = array_shift($ts);
		if (!$name->is('identifier')) {
			$this->issues[] = "{$name->range}: function requires a name, $name given";
			return null;
		}
		$body = array_shift($ts);
		if (!$body->is('group', '{}')) {
			$this->issues[] = "{$body->range}: function requires a body, $body found";
		}
		
		$name->context = 'func.name';
		$body->context = 'func.body';
		
		$f = new Node;
		$f->type  = 'def.func';
		$f->name  = $name;
		$f->body  = $this->parseBlock($body);
		return $f;
	}
	
	private function parseBlock(TokenGroup &$grp)
	{
		$b = new Node;
		$b->type  = 'block';
		$b->group = $grp;
		$b->nodes = array();
		$ts = $grp->tokens;
		while (count($ts)) {
			$s = $this->parseStmt($ts);
			if ($s)	$b->nodes[] = $s;
		}
		return $b;
	}
	
	private function parseStmt(array &$ts)
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
		return $this->parseExpr($sub);
	}
	
	private function parseExpr(array $ts)
	{
		foreach (static::$operators as $operators) {
			for ($i = 0; $i < count($ts); $i++) {
				if ($ts[$i]->is('symbol') && in_array($ts[$i]->text, $operators)) {
					return $this->parseBinOpExpr($ts[$i], array_slice($ts, 0, $i), array_slice($ts, $i+1));
				}
			}
		}
		
		if ($ts[0]->is('identifier')) return $this->parseIdentExpr(array_shift($ts), $ts);
		foreach ($ts as $t) {
			$this->issues[] = "{$t->range}: garbage $t in expression";
		}
		return null;
	}
	
	private function parseBinOpExpr($operator, array &$lts, array &$rts)
	{
		$operator->context = 'expr.op.binary';
		
		$o = new Node;
		$o->type  = 'expr.op.binary';
		$o->op    = $operator;
		$o->lhs   = $this->parseExpr($lts);
		$o->rhs   = $this->parseExpr($rts);
		$o->nodes = array($o->lhs, $o->rhs);
		return $o;
	}
	
	private function parseIdentExpr($ident, array &$ts)
	{
		if ($ts[0]->is('identifier')) {
			$type = array_shift($ts);
			
			foreach ($ts as $t) {
				$this->issues[] = "{$t->range}: garbage $t after variable expression";
			}
			
			$ident->context = 'expr.var.name';
			$type->context = 'expr.var.type';
			
			$v = new Node;
			$v->type = 'expr.var';
			$v->name = $ident;
			$v->type = $type;
			return $v;
		}
		return null;
	}
}
