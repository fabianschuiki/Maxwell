<?php

class Node
{
	public $kind;
	
	public function is($k) {
		return strpos($this->kind, $k) === 0;
	}
	
	public function & nodes() {
		switch ($this->kind) {
			case 'def.func':   return array_merge($this->in, $this->out, array(&$this->body)); break;
			case 'stmt.block': return $this->nodes; break;
			
			case 'stmt.if':    return array(&$this->condition, &$this->body, &$this->else); break;
			case 'stmt.else':  return array(&$this->body); break;
			case 'stmt.for':   return array(&$this->initial, &$this->condition, &$this->step, &$this->body); break;
			
			case 'expr.op.binary': return array(&$this->lhs, &$this->rhs); break;
			case 'expr.call':      return array_merge(array(&$this->callee), $this->args); break;
			case 'expr.call.arg':  return array(&$this->expr); break;
		}
		if (isset($this->nodes)) {
			echo $this->kind.' uses old nodes var'."\n";
			return $this->nodes;
		}
		return array();
	}
}
