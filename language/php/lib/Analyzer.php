<?php

class Analyzer
{
	public $nodes;
	public $scope;
	public $issues;
	
	public function run()
	{
		foreach ($this->nodes as $n) $this->reduce($n);
		if ($this->issues->isFatal()) return;
		
		$this->scope = new Scope;
		$this->addBuiltIn($this->scope);
		
		foreach ($this->nodes as $n) $this->populateScope($this->scope, $n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->bind($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->analyzeType($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->lateBind($n);
		if ($this->issues->isFatal()) return;
	}
	
	private $builtinNumericTypes = array();
	private function addBuiltIn(Scope &$scope)
	{
		$types = array('int', 'uint', 'float');
		for ($i = 8; $i <= 64; $i *= 2) {
			$types[] = 'int'.$i;
			$types[] = 'uint'.$i;
		}
		$types[] = "float32";
		$types[] = "float64";
		foreach ($types as $type) {
			$n = new Node;
			$n->builtin = true;
			$n->kind = 'def.type';
			$n->name = Token::builtin('identifier', $type);
			$n->c_name = $n->name->text.'_t';
			$n->c_ref = $n->c_name;
			$n->primitive = true;
			//$scope->names[$n->name->text] = $n;
			$this->populateScope($scope, $n);
			$this->builtinNumericTypes[] = $type;
			
			$operators = array('+', '-', '*', '/');
			foreach ($operators as $op) {
				$n = new Node;
				$n->builtin = true;
				$n->kind = 'def.func';
				$n->name = Token::builtin('identifier', $op);
				
				$a = new Node;
				$a->kind = 'def.func.arg';
				$a->type = Token::builtin('identifier', $type);
				$a->func = $n;
				
				$n->in = array(clone $a, clone $a);
				$n->out = array(clone $a);
				
				$this->populateScope($scope, $n);
				//$scope->names[$n->name->text][] = $n;
				$this->analyzeType($n);
			}
		}
		
		$n = new Node;
		$n->builtin = true;
		$n->kind = 'def.type';
		$n->name = Token::builtin('identifier', 'any');
		$n->c_name = 'unresolved_any';
		$this->populateScope($scope, $n);
		//$scope->add($this->issues, $n);
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
			$node->callee->name = $node->op->text;
		
			$arg = new Node;
			$arg->kind  = 'expr.call.arg';
			$arg->expr  = $node->expr;
		
			$node->args = array($arg);
		}
		if ($node->is('expr.op.binary')) {
			if ($node->op->text == '=' && $node->lhs->is('expr.var')) {
				$node->lhs->initial = $node->rhs;
				foreach ($node->lhs as $key => $value) {
					$node->$key = $value;
				}
				$node->name->node = $node;
				unset($node->rhs);
				unset($node->lhs);
				unset($node->op);
			} else {
				$node->kind = 'expr.call';
				$node->callee = new Node;
				$node->callee->kind = 'expr.ident';
				$node->callee->name = $node->op->text;
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
		if ($node->kind == 'def.func') {
			array_walk($node->in,  function(&$a) use ($f) { $a->func = $node; });
			array_walk($node->out, function(&$a) use ($f) { $a->func = $node; });
		}
	}
	
	private function populateScope(Scope &$parent, Node &$node)
	{
		if ($node->is('def') || ($node->is('stmt') && $node->kind != 'stmt.expr')) {
			$node->a_scope = new Scope($parent);
		} else {
			$node->a_scope = $parent;
		}
		switch ($node->kind) {
			case 'def.func':     $parent->add($this->issues, $node); break;
			case 'def.func.arg': $parent->add($this->issues, $node); break;
			case 'def.type':     $parent->add($this->issues, $node); break;
			case 'expr.var':     $parent->add($this->issues, $node); break;
		}
		foreach ($node->nodes() as $n) {
			$this->populateScope($node->a_scope, $n);
		}
	}
	
	private function bind(Node $node)
	{
		foreach ($node->nodes() as $n) {
			$this->bind($n);
		}
		switch ($node->kind) {
			case 'def.func.arg': {
				$type = $node->a_scope->find($node->type);
				if (!$type || $type->kind != 'def.type') {
					$this->issues[] = new Issue(
						'error',
						"Type '{$node->type}' of function argument '{$node->name}' is unknown.",
						$node->type->range,
						array($node->name->range)
					);
				}
				$node->type->a_target = $type;
				$node->a_target = $type;
			} break;
			case 'expr.var': {
				$type = $node->a_scope->find($node->type);
				if (!$type || $type->kind != 'def.type') {
					$this->issues[] = new Issue(
						'error',
						"Type '{$node->type}' of variable '{$node->name}' is unknown.",
						$node->type->range,
						array($node->name->range)
					);
				}
				$node->a_target = $type;
			} break;
			case 'expr.ident': {
				$target = $node->a_scope->find($node->name);
				if (!$target) {
					$this->issues[] = new Issue(
						'error',
						"Identifier '{$node->name}' is unknown.",
						$node->range
					);
				}
				$node->a_target = $target;
			} break;
			case 'expr.call': {
				$node->a_target = $node->callee->a_target;
			} break;
		}
	}
	
	private function analyzeType(Node &$node)
	{
		switch ($node->kind) {
			case 'expr.var': {
				$types = new TypeSet;
				$types->addNativeType($node->type);
				$node->a_types = $types;
				if (isset($node->initial)) {
					$node->initial->a_requiredTypes = clone $node->a_types;
				}
			} break;
			case 'def.func.arg': {
				$types = new TypeSet;
				$types->addNativeType($node->type);
				$node->a_types = $types;
			} break;
		}
		foreach ($node->nodes() as $n) {
			$this->analyzeType($n);
		}
		switch ($node->kind) {
			case 'def.func': {
				$type = new FuncType;
				foreach ($node->in as $a) {
					$type->addInput($a->a_types, $a->name->text);
				}
				foreach ($node->out as $a) {
					$type->addOutput($a->a_types, $a->name->text);
				}
				$node->a_types = $type;
			} break;
			case 'expr.var': {
				if (isset($node->initial->a_types)) {
					$node->a_types->intersect($node->initial->a_types);
				}
				//TODO: move this code to late binding as this will be similar for functions.
				if ($node->type->text == 'any') {
					if (!$node->a_types->unique()) {
						$this->issues[] = new Issue(
							'error',
							"Type of variable '{$node->name}' could not be inferred unambiguously. Possible types are '{$node->a_types}'.",
							$node->name->range
						);
					} else {
						$type = $node->a_types->unique();
						$node->a_target = $node->a_scope->find($type->name);
						//TODO: it is possible that this never happens as inexistent types should get caught way earlier than late binding. But just in case...
						if (!$node->a_target) {
							$this->issues[] = new Issue(
								'error',
								"Type of variable '{$node->name}' was inferred to be '{$type->name}', which is an unknown type.",
								$node->name->range
							);
						}
					}
				}
			} break;
			case 'expr.ident': {
				//TODO: No idea whether this works or not. This should help infer the type for variables with generic 'any' type, based on the variable's usage.
				if (isset($node->a_requiredTypes) && isset($node->a_target->a_types)) {
					$node->a_target->a_types->intersect($node->a_requiredTypes);
				}
				
				if (isset($node->a_target->a_types)) {
					$node->a_types = clone $node->a_target->a_types;
					$node->a_types->findCastTypes($node->a_scope);
				}
			} break;
			case 'expr.const.numeric': {
				$types = new TypeSet;
				$types->addNativeTypes($this->builtinNumericTypes);
				$types->findCastTypes($node->a_scope);
				$node->a_types = $types;
			} break;
			case 'expr.call': {
				$type = new FuncType;
				foreach ($node->args as $a) {
					$type->addInput($a->a_types, $a->name->text);
				}
				//TODO: Add the output variables. Requires the further specification of how return values are handled and assigned.
				$node->a_types = $type;
			} break;
			case 'expr.call.arg': {
				$node->a_types = clone $node->expr->a_types;
			} break;
		}
		
		//Types post processing.
		if (isset($node->a_types) && isset($node->a_requiredTypes)) {
			$node->a_types->intersect($node->a_requiredTypes);
		}
	}
	
	private function lateBind(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->lateBind($n);
		}
		switch ($node->kind) {
			case 'expr.call': {
				$matches = array();
				foreach ($node->a_target as $func) {
					$sec = $node->a_types->intersection($func->a_types);
					if ($sec) {
						$match = new stdClass;
						$match->type = $sec;
						$match->func = $func;
						$matches[] = $match;
					}
				}
				if (count($matches) < 1) {
					$this->issues[] = new Issue(
						'error',
						"Call to function '{$node->callee->name}' requires a function of type '{$node->a_types}', which does not exist.",
						$node->callee->name->range
					);
					return;
				}
				$lowestCost = null;
				foreach ($matches as $match) {
					$c = $match->type->cost();
					if ($lowestCost === null || $c < $lowestCost) {
						$lowestCost = $c;
					}
				}
				$matches = array_filter($matches, function($m) use ($lowestCost){
					return ($m->type->cost() <= $lowestCost);
				});
				if (count($matches) > 1) {
					$cs = implode("\n", array_map(function($m){ return strval($m->func->a_types); }, $matches));
					$this->issues[] = new Issue(
						'warning',
						"Call to function '{$node->callee->name}' with type '{$node->a_types}' is ambiguous. Candidates are:\n$cs",
						$node->callee->name->range
					);
				}
				$node->a_target = $matches[0]->func;
			} break;
		}
	}
}
