<?php

class Node
{
	public $kind;
	
	public function is($k) {
		return strpos($this->kind, $k) === 0;
	}
	
	public function & nodes() {
		$n = null;
		switch ($this->kind) {
			case 'def.func':     $n = array_merge($this->in, $this->out, array(&$this->body)); break;
			case 'def.func.arg': $n = array(&$this->type); break;
			case 'stmt.block':   $n = $this->nodes; break;
			case 'stmt.expr':    $n = array(&$this->expr); break;
			
			case 'stmt.if':    $n = array(&$this->condition, &$this->body, &$this->else); break;
			case 'stmt.else':  $n = array(&$this->body); break;
			case 'stmt.for':   $n = array(&$this->initial, &$this->condition, &$this->step, &$this->body); break;
			
			case 'expr.op.unary':  $n = array(&$this->expr); break;
			case 'expr.op.binary': $n = array(&$this->lhs, &$this->rhs); break;
			case 'expr.call':      $n = array_merge(array(&$this->callee), $this->args); break;
			case 'expr.call.arg':  $n = array(&$this->expr); break;
			case 'expr.var':       $n = array(&$this->type, &$this->initial); break;
			case 'expr.tuple': $n = $this->exprs; break;
		}
		if (isset($n)) {
			return array_filter($n, function($a){ return $a != NULL; });
		}
		if (isset($this->nodes)) {
			echo $this->kind.' uses old nodes var'."\n";
			return $this->nodes;
		}
		return array();
	}
}
