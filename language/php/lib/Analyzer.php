<?php

class Analyzer
{
	public $nodes;
	public $issues;
	
	public function run()
	{
		$this->issues = array();
		$this->eachNode('reduceNode', $this->nodes);
		/*$rootScope = new Scope;
		foreach ($this->nodes as $n) { $this->analyzeScopes($n, $rootScope); }
		foreach ($this->nodes as $n) { $this->analyzeTypes($n); }
		foreach ($this->nodes as $n) { $this->matchFunctions($n); }*/
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
	}
	
	private function eachNode($func, array &$nodes)
	{
		foreach ($nodes as &$node) {
			$this->eachNode($func, $node->nodes());
			$node = call_user_func(array($this, $func), $node);
		}
	}
	
	private function reduceNode(Node &$node)
	{
		if ($node->is('expr.op.unary')) {
			$f = new Node;
			$f->kind = 'expr.call';
			$f->callee = new Node;
			$f->callee->kind = 'expr.ident';
			$f->callee->name = 'unary_';
			for ($i = 0; $i < strlen($node->op->text); $i++)
				$f->callee->name .= sprintf('%02X', ord($node->op->text[$i]));
		
			$arg = new Node;
			$arg->kind  = 'expr.call.arg';
			$arg->expr  = $node->expr;
		
			$f->args = array($arg);
			return $f;
		}
		if ($node->is('expr.op.binary')) {
			if ($node->op->text == '=' && $node->lhs->is('expr.var')) {
				$node->lhs->initial = $node->rhs;
				return $node->lhs;
			} else {
				$f = new Node;
				$f->kind = 'expr.call';
				$f->callee = new Node;
				$f->callee->kind = 'expr.ident';
				$f->callee->name = 'operator_';
				for ($i = 0; $i < strlen($node->op->text); $i++)
					$f->callee->name .= sprintf('%02X', ord($node->op->text[$i]));
			
				$lhs = new Node;
				$lhs->kind  = 'expr.call.arg';
				$lhs->expr  = $node->lhs;
			
				$rhs = new Node;
				$rhs->kind  = 'expr.call.arg';
				$rhs->expr  = $node->rhs;
			
				$f->args = array($lhs, $rhs);
				return $f;
			}
		}
		return $node;
	}
	
	public function analyzeScopes(Node &$node, Scope &$parent)
	{
		if ($node->is('expr')) {
			$node->scope = $parent;
			switch ($node->kind) {
				case 'expr.var':   $node->scope->names[$node->name->text] = $node; break;
				case 'expr.ident': {
					$node->target = $node->scope->find($node->name->text);
					if (!$node->target) {
						$this->issues[] = "{$node->name->range}: unable to resolve identifier {$node->name->text}";
					}
				}
			}
		} else {
			$node->scope = new Scope($parent);
			switch ($node->kind) {
				case 'def.func': {
					$fn = $node->name->text;
					if (!isset($parent->names[$fn])) {
						$parent->names[$fn] = $node;
					} else {
						$parent->names[$fn]->nodes += $node->nodes;
					}
				} break;
			}
		}
		if (isset($node->nodes)) {
			foreach ($node->nodes as $n) {
				$this->analyzeScopes($n, $node->scope);
			}
		}
	}
	
	public function analyzeTypes(Node &$node)
	{
		if ($node->is('expr')) {
			if (!isset($node->a_requiredType)) {
				$node->a_requiredType = new Type;
			}
			if (!isset($node->a_possibleType)) {
				$node->a_possibleType = new Type;
			}
			switch ($node->kind) {
				case 'expr.const.numeric': $node->a_possibleType = new Type('int', 'float'); break;
				case 'expr.const.string':  $node->a_possibleType = new Type('string'); break;
				case 'expr.var':           $node->a_possibleType = new Type($node->type->text); break;
				case 'expr.op.binary': {
					$this->analyzeTypes($node->lhs);
					$this->analyzeTypes($node->rhs);
					
					$node->a_possibleType = $node->lhs->a_type->intersection($node->rhs->a_type);
					$node->lhs->a_requiredType = $node->a_possibleType;
					$node->rhs->a_requiredType = $node->a_possibleType;
					
					$this->analyzeTypes($node->lhs);
					$this->analyzeTypes($node->rhs);
					
					if (!count($node->a_possibleType->a_types)) {
						$this->issues[] = "{$node->op->range}: binary operator requires both sides to be of equal type, which is impossible for {$node->lhs->a_possibleType} and {$node->rhs->a_possibleType}";
					}
				} break;
				case 'expr.ident': {
					if ($node->target) {
						$node->a_possibleType = $node->target->a_type;
					}
				} break;
				case 'expr.call': {
					foreach ($node->args as $a) {
						$this->analyzeTypes($a);
					}
					$node->a_possibleType = new Type;
				} break;
				case 'expr.call.arg': {
					$this->analyzeTypes($node->expr);
					$node->a_possibleType = $node->expr->a_possibleType;
				} break;
			}
			if (isset($node->a_possibleType)) {
				$node->a_type = $node->a_possibleType->intersection($node->a_requiredType);
			}
		} else {
			if (isset($node->nodes)) {
				foreach ($node->nodes as $n) {
					$this->analyzeTypes($n);
				}
			}
		}
	}
	
	public function matchFunctions(Node &$node)
	{
		if ($node->is('expr.ident') && isset($node->target) && $node->target->is('def.func')) {
			$patterns = $node->target->nodes;
			//TODO: implement some pattern matching...
		}
		if (isset($node->nodes)) {
			foreach ($node->nodes as $n) {
				$this->matchFunctions($n);
			}
		}
	}
}
