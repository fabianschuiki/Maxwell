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
		
	issues:
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
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
			$n->primitive = true;
			$scope->names[$n->name->text] = $n;
			$this->builtinNumericTypes[] = $n;
			
			$operators = array('+', '-', '*', '/');
			foreach ($operators as $op) {
				$n = new Node;
				$n->builtin = true;
				$n->kind = 'def.func';
				$n->name = Token::builtin('identifier', $op);
				
				$a = new Node;
				$a->kind = 'def.func.arg';
				$a->type = Token::builtin('identifier', $type);
				
				$n->in = array(clone $a, clone $a);
				$n->out = array(clone $a);
				
				$scope->names[$n->name->text][] = $n;
				$this->analyzeType($n);
			}
		}
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
	}
	
	private function populateScope(Scope &$parent, Node &$node)
	{
		if ($node->is('def') || ($node->is('stmt') && $node->kind != 'stmt.expr')) {
			$node->a_scope = new Scope($parent);
		} else {
			$node->a_scope = $parent;
		}
		switch ($node->kind) {
			case 'def.func': {
				if (!isset($parent->names[$node->name->text])) {
					$parent->names[$node->name->text] = array();
				}
				$parent->names[$node->name->text][] = $node;
			} break;
			case 'def.func.arg': {
				//$parent->names[$node->name->text] = $node;
				$node->type->a_target = $node->a_scope->find($node->type->text);
				if (!$node->type->a_target) {
					$this->issues[] = new Issue(
						'error',
						"type '{$node->type->text}' of function argument '{$node->name->text}' is unknown",
						$node->type->range,
						array($node->name->range)
					);
				}
			} break;
			case 'def.type':   $parent->names[$node->name->text] = $node; break;
			case 'expr.var': {
				$parent->names[$node->name->text] = $node;
				$node->type->a_target = $node->a_scope->find($node->type->text);
				if (!$node->type->a_target) {
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
				$node->a_local = ($node->type->text == 'scalar');
				if ($node->initial) {
					$node->initial->a_reqType = $node->a_type;
				}
			} break;
			case 'expr.const.numeric': $node->a_type = new Type('int', 'float'); break;
			case 'expr.ident': $node->a_type = ($node->a_target ? $node->a_target->a_type : null); break;
			case 'expr.call': {
				$funcs = $node->callee->a_target;
				if (!is_array($funcs)) {
					$this->issues[] = new Issue(
						'error',
						"called function '{$node->callee->name}' is unknown",
						$node->callee->range
					);
				} else {
					$matches = array();
					foreach ($funcs as $f) {
						if (count($f->in) != count($node->args)) {
							continue;
						}
						$match = true;
						$implicitCasts = 0;
						$casts = array();
						for ($i = 0; $i < count($f->in) && $match; $i++) {
							$arg = $f->in[$i];
							$cast = $this->getCastSequence($node->a_scope, $node->args[$i]->a_type, $arg->a_type);
							if ($cast === null) {
								$match = false;
							} else {
								$implicitCasts += count($cast);
								$casts[$i] = $cast;
								/*$t = $f->in[$i]->a_type->intersection($node->args[$i]->a_type);
								if (!count($t->types)) {
									$match = false;
								}*/
							}
						}
						if ($match) {
							$matches[] = array(
								'func' => $f,
								'cast' => $casts
							);
							if ($implicitCasts == 0) {
								break;
							}
						}
					}
					if (!count($matches)) {
						$this->issues[] = new Issue(
							'error',
							"Called function '{$node->callee->name}' has no type matching the call. Candidates are:\n- ".implode("\n- ", array_map(function($f){
								return $f->a_type;
							}, $funcs)),
							$node->callee->range
						);
					} else {
						$node->a_target = $matches[0]['func'];
						foreach ($matches[0]['cast'] as $arg => $casts) {
							$orig = $node->args[$arg];
							$wrap = $node->args[$arg]->expr;
							foreach ($casts as $cast) {
								$n = new Node;
								$n->kind = 'expr.call';
								$n->callee = new Node;
								$n->callee->kind = 'expr.ident';
								$n->callee->name = $cast->name->text;
								$n->callee->range = clone $orig->expr->range;
								$n->a_target = $cast;
								$na = new Node;
								$na->kind = 'expr.call.arg';
								$na->expr = $wrap;
								$n->args = array($na);
								//$this->analyzeType($n);
								$wrap = $n;
								//echo "applying cast {$c->a_type}\n";
							}
							$node->args[$arg]->expr = $wrap;
						}
					}
				}
			} break;
			case 'expr.call.arg': $node->a_type = $node->expr->a_type; break;
		}
	}
	
	private function getCastSequence(Scope &$scope, Type &$from, Type &$to)
	{
		if (count($from->intersection($to)->types)) {
			return array();
		}
		echo "trying to find cast from $from to $to\n";
		$casts = $scope->find('cast');
		if (!is_array($casts)) {
			return null;
		}
		foreach ($casts as $f) {
			if (count($f->in) != 1 || count($f->out) != 1) {
				continue;
			}
			if (count($from->intersection($f->in[0]->a_type)) && count($to->intersection($f->out[0]->a_type))) {
				return array($f);
			}
		}
		return null;
	}
}
