<?php

class Analyzer
{
	public $nodes;
	public $issues;
	
	public function run()
	{
		$this->issues = array();
		
		foreach ($this->nodes as $n) $this->reduce($n);
		if (count($this->issues)) goto issues;
		
		$scope = new Scope;
		$this->addBuiltIn($scope);
		
		foreach ($this->nodes as $n) $this->populateScope($scope, $n);
		if (count($this->issues)) goto issues;
		
		foreach ($this->nodes as $n) $this->analyzeType($n);
		if (count($this->issues)) goto issues;
		
		/*$rootScope = new Scope;
		foreach ($this->nodes as $n) { $this->analyzeScopes($n, $rootScope); }
		foreach ($this->nodes as $n) { $this->analyzeTypes($n); }
		foreach ($this->nodes as $n) { $this->matchFunctions($n); }*/
		
	issues:
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
	}
	
	private function addBuiltIn(Scope &$scope)
	{
		$this->addBuiltInType($scope, 'Type');
		$this->addBuiltInType($scope, 'int');
		
		$n = new Node;
		$n->kind = 'def.func';
		$n->name = 'showType';
		$scope->names['showType'] = $n;
		
		$n = clone $n;
		$n->name = 'show';
		$scope->names['show'] = $n;
		
		$n = new Node;
		$n->kind = 'def.func';
		$n->name = 'binary_equal';
		$scope->names['operator=='] = $n;
		
		$this->addBuiltInFunc($scope, 'binary=');
	}
	
	private function addBuiltInType(Scope &$scope, $name)
	{
		$n = new Node;
		$n->kind = 'def.type';
		$n->name = $name;
		$n->builtin = true;
		$scope->names[$name] = $n;
	}
	
	private function addBuiltInFunc(Scope &$scope, $name)
	{
		$n = new Node;
		$n->kind = 'def.func';
		$n->name = str_replace(array(
			'='
		), array(
			'_equal'
		), $name);
		$scope->names[$name] = $n;
	}
	
	private function reduce(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->reduce($n);
		}
		if ($node->is('expr.op.unary')) {
			$node->kind = 'expr.call';
			$node->callee = new Node;
			$node->callee->kind = 'expr.ident';
			$node->callee->name = 'unary'.$node->op->text;
		
			$arg = new Node;
			$arg->kind  = 'expr.call.arg';
			$arg->expr  = $node->expr;
		
			$node->args = array($arg);
		}
		if ($node->is('expr.op.binary')) {
			if ($node->op->text == '=' && $node->lhs->is('expr.var')) {
				$node->lhs->initial = $node->rhs;
				return $node->lhs;
			} else {
				$node->kind = 'expr.call';
				$node->callee = new Node;
				$node->callee->kind = 'expr.ident';
				$node->callee->name = 'binary'.$node->op->text;
				$node->callee->range = clone $node->op->range;
				unset($node->op);
			
				$lhs = new Node;
				$lhs->kind  = 'expr.call.arg';
				$lhs->expr  = $node->lhs;
				unset($node->lhs);
			
				$rhs = new Node;
				$rhs->kind  = 'expr.call.arg';
				$rhs->expr  = $node->rhs;
				unset($node->rhs);
				
				$node->args = array($lhs, $rhs);
			}
		}
	}
	
	private function populateScope(Scope &$parent, Node &$node)
	{
		if ($node->is('def') || $node->is('stmt')) {
			$node->a_scope = new Scope($parent);
		} else {
			$node->a_scope = $parent;
		}
		switch ($node->kind) {
			case 'def.func':   $parent->names[$node->name->text] = $node; break;
			case 'def.type':   $parent->names[$node->name->text] = $node; break;
			case 'expr.var': {
				$parent->names[$node->name->text] = $node;
				$node->a_target = $node->a_scope->find($node->type->text);
				if (!$node->a_target) {
					$this->issues[] = new Issue(
						'error',
						"type '{$node->type->text}' of variable '{$node->name->text}' is unknown",
						$node->type->range,
						array($node->name->range)
					);
				}
			} break;
			case 'expr.ident': {
				$node->a_target = $node->a_scope->find($node->name);
				if (!$node->a_target) {
					$this->issues[] = new Issue(
						'error',
						"identifier '{$node->name}' unknown",
						$node->range
					);
				}
			} break;
		}
		foreach ($node->nodes() as $n) {
			$this->populateScope($node->a_scope, $n);
		}
	}
	
	public function analyzeType(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->analyzeType($n);
		}
		switch ($node->kind) {
			case 'def.func': {
				$in  = array();
				$out = array();
				foreach ($node->in as $a)  $in[]  = $a->a_type;
				foreach ($node->out as $a) $out[] = $a->a_type;
				$node->a_type = new Type('('.implode(',', $in).') -> ('.implode(',', $out).')');
			} break;
			case 'def.func.arg': {
				$node->a_type = new Type($node->type->text);
			} break;
			case 'expr.var': {
				$node->a_type = new Type($node->type->text);
				if ($node->initial) {
					$node->initial->a_reqType = $node->a_type;
				}
			} break;
			case 'expr.const.numeric': $node->a_type = new Type('int', 'float'); break;
			case 'expr.ident': $node->a_type = ($node->a_target ? $node->a_target->a_type : null); break;
		}
	}
	
	public function analyzeTypes_old(Node &$node)
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
