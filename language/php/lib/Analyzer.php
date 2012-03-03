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
			case 'def.func':     $parent->add($this->issues, $node); break;
			case 'def.func.arg': $parent->add($this->issues, $node);  break;
			case 'def.type':     $parent->add($this->issues, $node); break;
			case 'expr.var':     $parent->add($this->issues, $node);  break;
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
				$node->type->a_target = $type;
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
		}
	}
	
	private function analyzeType(Node &$node)
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
						//echo "trying {$f->name} {$f->a_type}\n";
						$match = true;
						$implicitCasts = 0;
						$casts = array();
						for ($i = 0; $i < count($f->in) && $match; $i++) {
							$arg = $f->in[$i];
							$cast = $this->getCastSequence($node->a_scope, $node->args[$i]->a_type, $arg->a_type);
							if ($cast === null) {
								//echo "- no cast available\n";
								$match = false;
							} else {
								$implicitCasts += count($cast);
								$casts[$i] = $cast;
								//echo "- cast over ".count($cast)." available\n";
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
						usort($matches, function($a,$b) {
							if (count($a['cast']) < count($b['cast'])) return 1;
							if (count($a['cast']) > count($b['cast'])) return -1;
							return 0;
						});
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
		$casts = $scope->find('cast');
		if (!is_array($casts)) {
			return null;
		}
		foreach ($casts as $f) {
			if (count($f->in) != 1 || count($f->out) != 1) {
				continue;
			}
			if (count($from->intersection($f->in[0]->a_type)->types) && count($to->intersection($f->out[0]->a_type)->types)) {
				return array($f);
			}
		}
		return null;
	}
}
