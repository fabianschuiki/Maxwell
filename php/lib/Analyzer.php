<?php

class Analyzer
{
	public $nodes;
	public $importScope;
	public $scope;
	public $issues;
	
	public function run()
	{
		//Build the initial Language Entity Tree.
		$scope = new LET\Scope;
		foreach ($this->nodes as $node) {
			$this->buildEntity($scope, $node);
		}
		
		//Bind the identifiers where possible.
		$scope->bind();
		
		$this->scope = $scope;
		
		/*foreach ($this->nodes as $n) $this->reduce($n);
		if ($this->issues->isFatal()) return;
		
		$builtinScope = new Scope;
		$this->addBuiltIn($builtinScope);
		if (!$this->importScope) {
			$this->importScope = new Scope($builtinScope);
		} else {
			$this->importScope->parent = $builtinScope;
		}
		$this->scope = new Scope($this->importScope);
		
		foreach ($this->nodes as $n) $this->populateScope($this->scope, $n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->bind($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->analyzeType($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->resolveMember($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->lateBind($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->incarnate($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->expandTupleOps($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->lateBind($n);
		if ($this->issues->isFatal()) return;
		
		foreach ($this->nodes as $n) $this->generateCName($n);
		if ($this->issues->isFatal()) return;*/
	}
	
	private function buildEntity(LET\Scope $scope, AST\Node $node)
	{
		switch ($node->kind()) {
			case 'TypeStmt': new LET\Type_AST($scope, $node); break;
			case 'FuncStmt': new LET\Func_AST($scope, $node); break;
			default: {
				global $issues;
				$issues[] = new \Issue(
					'warning',
					"{$node->nice()} is not allowed at file level. Ignored.",
					$node
				);
			} break;
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
			$n->c_ref = $n->c_name;
			$n->primitive = true;
			//$scope->names[$n->name->text] = $n;
			$this->populateScope($scope, $n);
			$this->builtinNumericTypes[] = $type;
			
			/*$operators = array('+', '-', '*', '/', '=');
			foreach ($operators as $op) {
				$this->addBuiltInBinOp($scope, $op, $type);
			}*/
		}
		
		$types = array('String');
		foreach ($types as $type) {
			$n = new Node;
			$n->builtin = true;
			$n->kind = 'def.type';
			$n->name = Token::builtin('identifier', $type);
			$n->c_name = $n->name.'_t';
			$n->c_ref = $n->c_name.'*';
			$this->populateScope($scope, $n);
		}
		
		
		$operators = array('+', '-', '*', '/', '=', '==', '!=', '<', '>', '<=', '>=');
		foreach ($operators as $op) {
			$this->addBuiltInBinOp($scope, $op);
		}
		
		$n = new Node;
		$n->builtin = true;
		$n->kind = 'def.type';
		$n->name = Token::builtin('identifier', 'any');
		$n->c_name = 'unresolved_any';
		$this->populateScope($scope, $n);
		//$scope->add($this->issues, $n);
	}
	
	private function addBuiltInBinOp(Scope &$scope, $op)
	{
		$n = new Node;
		$n->builtin = true;
		$n->kind = 'def.func';
		$n->name = Token::builtin('identifier', $op);
		
		$a = new Node;
		$a->kind = 'def.func.arg';
		$a->type = new Node;
		$a->type->kind = 'type.var';
		$a->type->name = Token::builtin('identifier', '@a');
		$a->type->range = clone $a->type->name->range;
		
		$b = clone $a;
		$c = clone $a;
		
		$t = new TypeVar('@a');
		$a->type->a_types = $t;
		$b->type->a_types = $t;
		$c->type->a_types = $t;
		
		$n->in = array($a, $b);
		$n->out = array($c);
		
		$this->populateScope($scope, $n);
		//$this->bind($n);
		$this->analyzeType($n);
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
				$node->callee->name = $node->op;
				$node->callee->range = clone $node->op->range;
				$node->range = clone $node->callee->range;
				$node->op->node = $node;
				unset($node->op);
			
				$lhs = new Node;
				$lhs->kind  = 'expr.call.arg';
				$lhs->expr  = $node->lhs;
				$lhs->range = $node->lhs->range;
				$node->range->combine($lhs->range);
				unset($node->lhs);
			
				$rhs = new Node;
				$rhs->kind  = 'expr.call.arg';
				$rhs->expr  = $node->rhs;
				$rhs->range = $node->rhs->range;
				$node->range->combine($rhs->range);
				unset($node->rhs);
				
				$node->args = array($lhs, $rhs);
			}
		}
		if ($node->kind == 'def.func') {
			array_walk($node->in,  function(&$a) use ($f) { $a->func = $node; });
			array_walk($node->out, function(&$a) use ($f) { $a->func = $node; });
			$node->a_incarnations = array();
		}
	}
	
	private function populateScope(Scope &$parent, Node &$node)
	{
		$individuallyScoped = array(
			'def.func', 'def.type'
		);
		//if (($node->is('def') && !$node->builtin) || ($node->is('stmt') && $node->kind != 'stmt.expr')) {
		if (in_array($node->kind, $individuallyScoped)) {
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
		if (!$node->builtin) {
			foreach ($node->nodes() as $n) {
				$this->populateScope($node->a_scope, $n);
			}
		}
	}
	
	private function generateCName(Node $node)
	{
		foreach ($node->nodes() as $n) {
			$this->generateCName($n);
		}
		switch ($node->kind) {
			case 'def.func': {
				$funcs = $node->a_scope->find(strval($node->name));
				$i = 0;
				do {
					$node->c_name = 'func_'.Compiler::makeCIdent($node->name.'_'.strval($node->a_types));
					if ($i > 0) $node->c_name .= $i;
					$collides = false;
					foreach ($funcs as $func) {
						if ($func != $node && $func->c_name == $node->c_name) {
							$collides = true;
							break;
						}
					}
					$i++;
				} while ($collides == true);
			} break;
			case 'def.type': {
				$node->c_name = Compiler::makeCIdent(strval($node->name))."_t";
			} break;
		}
	}
	
	private function bind(Node $node)
	{
		foreach ($node->nodes() as $n) {
			$this->bind($n);
		}
		switch ($node->kind) {
			/*case 'def.func.arg': {
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
			} break;*/
			/*case 'expr.var': {
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
			} break;*/
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
				$node->callee->a_late = true;
				$node->a_target = $node->callee->a_target;
			} break;
			
			case 'type.var': {
				$var = $node->a_scope->find($node->name);
				if (!$var) {
					$node->a_scope->add($this->issues, $node); break;
				} else {
					$node->a_target = $var;
				}
			} break;
			case 'type.name': {
				$type = $node->a_scope->find($node->name);
				if (!$type || $type->kind != 'def.type') {
					$this->issues[] = new Issue(
						'error',
						"Type '{$node->name}' is unknown.",
						$node->range
					);
				}
				$node->a_target = $type;
			} break;
		}
	}
	
	private function analyzeType(Node &$node, $deep = true)
	{
		switch ($node->kind) {
			case 'expr.var': {
				if ($deep) {
					$this->analyzeType($node->type);
				}
				$node->a_types = $node->type->a_types;
				if (isset($node->initial)) {
					$node->initial->a_requiredTypes = clone $node->a_types;
				}
			} break;
			case 'type.name': {
				$node->a_types = new NamedType(strval($node->name));
			} break;
		}
		
		if ($deep) {
			if ($node->kind == 'expr.var') {
				if ($node->initial) {
					$this->analyzeType($node->initial);
				}
			} else {
				foreach ($node->nodes() as $n) {
					$this->analyzeType($n);
				}
			}
			if ($this->issues->isFatal()) {
				return;
			}
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
				$node->a_generic = $type->isGeneric();
			} break;
			case 'def.func.arg': {
				/*$types = new TypeSet;
				 $types-*>addNativeType($node->type);*/
				$node->a_types = $node->type->a_types;
			} break;
			case 'expr.var': {
				if (isset($node->initial->a_types)) {
					$node->a_types = $node->initial->a_types;
				}
				/*//TODO: move this code to late binding as this will be similar for functions.
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
				}*/
			} break;
			case 'expr.ident': {
				//TODO: No idea whether this works or not. This should help infer the type for variables with generic 'any' type, based on the variable's usage.
				/*if (isset($node->a_requiredTypes) && isset($node->a_target->a_types)) {
					$node->a_target->a_types->intersect($node->a_requiredTypes);
				}*/
				
				if (isset($node->a_target->a_types)) {
					$node->a_types = clone $node->a_target->a_types;
					//TODO: Improve this by moving the cast type finding somewhere else. Maybe the scope or the analyzer itself.
					if (!$node->a_types instanceof TypeSet) {
						$node->a_types = new TypeSet($node->a_types);
					}
					$node->a_types->findCastTypes($node->a_scope);
					//TODO: Incorporate this chunk into findCastTypes.
					if (count($node->a_types->types) == 1) {
						$node->a_types = $node->a_types->types[0];
					}
				}
			} break;
			case 'expr.const.numeric': {
				$types = new TypeSet;
				$types->addNativeTypes($this->builtinNumericTypes);
				$types->findCastTypes($node->a_scope);
				$node->a_types = $types;
			} break;
			case 'expr.const.string': {
				$types = new TypeSet;
				$types->addNativeType('String');
				$types->findCastTypes($node->a_scope);
				$node->a_types = $types;
			} break;
			case 'expr.call': {
				$type = new FuncType;
				foreach ($node->args as $a) {
					$type->addInput($a->a_types, $a->name->text);
				}
				if ($node->a_requiredTypes) {
					$req = $node->a_requiredTypes;
					if ($req instanceof TupleType) {
						foreach ($req->fields as $f) {
							$type->addOutput($f->type, $f->name);
						}
					} else {
						$type->addOutput($req);
					}
				}
				//TODO: Add the output variables. Requires the further specification of how return values are handled and assigned.
				//$type->addOutput(new TypeSet);
				$node->a_functype = $type;
				$node->a_types = /*$type->out*/new TypeSet;
			} break;
			case 'expr.call.arg': {
				if ($node->expr->a_types) {
					$node->a_types = clone $node->expr->a_types;
				}
			} break;
			case 'expr.tuple': {
				$types = new TupleType;
				foreach ($node->exprs as $e) {
					$types->addField($e->a_types);
				}
				$node->a_types = $types;
			} break;
			case 'type.var': {
				if (!$node->a_types) {
					if ($node->a_target) {
						$node->a_types = $node->a_target->a_types;
					} else {
						$node->a_types = new TypeVar(strval($node->name));
					}
				}
			} break;
			case 'expr.member': {
				$types = $node->expr->a_types;
				//echo "resolving member '{$node->member}'\n";
				//echo " -> @expr: '{$types}'\n";
				if (!$types instanceof TypeSet) {
					$types = new TypeSet($types);
				}
				$possibleMembers = array();
				foreach ($types->types as $type) {
					if (!$type instanceof NamedType) {
						$this->issues[] = new Issue(
							'warning',
							"Member access to tuples is not yet supported.",
							$node->range
						);
						continue;
					}
					//echo "- {$type}\n";
					$typedef = $node->a_scope->find($type->name);
					if ($typedef) {
						//echo "- > {$typedef->name}\n";
						$member = $typedef->a_scope->find(strval($node->member));
						if ($member) {
							$possibleMembers[$type->name] = $member;
						}
					}
				}
				//TODO: Impose type restrictions here based on field access.
				if (count($possibleMembers) == 0) {
					$this->issues[] = new Issue(
						'error',
						"Member '{$node->member}' unknown for expression of type '{$type}'.",
						$node->range
					);
				} else {
					foreach ($possibleMembers as $type => $member) break;
					if (count($possibleMembers) > 1) {
						$this->issues[] = new Issue(
							'warning',
							"Accessing member '{$node->member}' of expression of type '{$types}' is ambiguous. Assuming type '{$type}'.",
							$node->range
						);
					}
					$node->a_target = $member;
					$node->a_types = $member->a_types;
				}
			} break;
		}
		
		//Types post processing.
		if (isset($node->a_types)) {
			if (isset($node->a_requiredTypes)) {
				$node->a_types = $node->a_types->match($node->a_requiredTypes);
			}
		} else if ($node->is('expr') && !$node->a_late && $node->kind != 'expr.member') {
			$this->issues[] = new Issue(
				'error',
				"Unable to infer type of '{$node->kind}'.",
				$node->range
			);
		}
	}
	
	private function resolveMember(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->resolveMember($n);
		}
		if ($this->issues->isFatal()) {
			return;
		}
		
		if ($node->kind == 'expr.member') {
			//echo "resolving member '{$node->member}'\n";
			//echo " -> expr: '{$node->expr->a_types}'\n";
			/*$target = $node->a_scope->find(strval($node->member));
			if (!$target) {
				$this->issues[] = new Issue(
					'error',
					"Member '{$node->member}' is not known",
					$node->range
				);
			}
			$node->a_target = $target;*/
		}
	}
	
	private function lateBind(Node &$node)
	{
		$changed = false;
		foreach ($node->nodes() as $n) {
			$types = $n->a_types;
			$this->lateBind($n);
			if ($types != $n->a_types) {
				$changed = true;
			}
		}
		
		//In case the late binding changed the inferred type of any of our subnodes we have to re-evaluate.
		if (changed) {
			$this->analyzeType($node, false);
		}
		
		switch ($node->kind) {
			case 'expr.call': {
				if (is_array($node->a_target)) {
					$matches = array();
					foreach ($node->a_target as $func) {
						assert($node->a_functype);
						$sec = $node->a_functype->match($func->a_types);
						//$sec = $func->a_types->match($node->a_functype);
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
							"Call to function '{$node->callee->name}' requires a function of type '{$node->a_functype}', which does not exist.",
							$node->callee->name->range
						);
						return;
					}
					$lowestCost = null;
					$lowestAbstraction = null;
					foreach ($matches as $match) {
						$c = $match->type->cost();
						$a = $match->func->a_types->getAbstractionLevel();
						if ($lowestCost === null || $c < $lowestCost) {
							$lowestCost = $c;
						}
						if ($lowestAbstraction === null || $a < $lowestAbstraction) {
							$lowestAbstraction = $a;
						}
					}
					$matches = array_filter($matches, function($m) use ($lowestCost, $lowestAbstraction){
						return ($m->type->cost() <= $lowestCost && $m->func->a_types->getAbstractionLevel() <= $lowestAbstraction);
					});
					if (count($matches) > 1) {
						//echo "lowest abstraction: $lowestAbstraction\n";
						$cs = implode("\n", array_map(function($m){
							return strval($m->func->a_types).' ('.$m->func->a_types->getAbstractionLevel().')';
						}, $matches));
						$this->issues[] = new Issue(
							'warning',
							"Call to function '{$node->callee->name}' with type '{$node->a_types}' is ambiguous. Candidates are:\n$cs",
							$node->callee->name->range
						);
					}
					//var_dump($matches);
					$match = array_shift($matches);
					if ($match->func->builtin || !$match->func->a_generic) {
						$node->a_target = $match->func;
						$node->a_types  = $match->type->out;
						if (count($node->a_types->fields) == 1) {
							$node->a_types = $node->a_types->fields[0]->type;
						}
					} else {
						$inc = null;
						foreach ($match->func->a_incarnations as $i) {
							if ($i->type == $match->type) {
								$inc = $i;
								break;
							}
						}
						if (!$inc) {
							$inc = new Node;
							$inc->kind = 'def.func.incarnation';
							$inc->func = $match->func;
							$inc->type = $match->type;
							$inc->a_types = $inc->type;
							$match->func->a_incarnations[] = $inc;
							
							$node->a_target = $inc;
							$node->a_types  = $inc->type->out;
						}
					}
				} else if ($node->a_target->kind == 'def.func.incarnation') {
					$node->a_target = $node->a_target->inc_func;
				}
			} break;
			
			case 'expr.var':
			case 'def.func.arg': {
				if (isset($node->a_types) && $node->a_types instanceof NamedType) {
					$t = $node->a_scope->find($node->a_types->name);
					if (!$t) {
						if ($node->kind == 'expr.var') {
							$msg = "Type '{$node->a_types->name}' of variable '{$node->name}' is unknown.";
						} else {
							$msg = "Type '{$node->a_types->name}' of argument '{$node->name}' of function '{$node->func->name}' is unknown.";
						}
						$this->issues[] = new Issue(
							'error',
							$msg,
							$node->range
						);
					}
					$node->a_target = $t;
				}
			} break;
		}
	}
	
	private function incarnate(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->incarnate($n);
		}
		if ($node->kind == 'def.func.incarnation') {
			$func = $node->func->makeClone();
			
			$this->populateScope($node->func->a_scope->parent, $func);
			$this->bind($func);
			$this->analyzeType($func);
			$func->a_types->match($node->type);
			$this->resolveTypeVars($func);
			$this->analyzeType($func);
			//$this->lateBind($func);
			
			$node->inc_func = $func;
		}
	}
	
	private function resolveTypeVars(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->resolveTypeVars($n);
		}
		if ($node->a_types && $node->a_types instanceof TypeVar) {
			if (!$node->a_types->type instanceof TypeSet) {
				$node->a_types = $node->a_types->type;
			}
		}
	}
	
	private function expandTupleOps(Node &$node)
	{
		foreach ($node->nodes() as $n) {
			$this->expandTupleOps($n);
		}
		if ($node->is('expr.call') && $node->a_target->builtin && count($node->args) == 2) {
			$this->analyzeType($node);
			if ($node->args[0]->a_types instanceof TupleType && $node->args[1]->a_types instanceof TupleType) {
				$a = $node->args[0]->expr;
				$b = $node->args[1]->expr;
				
				$pairs = array();
				for ($i = 0; $i < count($a->exprs) && $i < count($b->exprs); $i++) {
					$pairs[] = array($a->exprs[$i], $b->exprs[$i]);
				}
				
				$node->exprs = array();
				foreach ($pairs as $pair) {
					$a = $pair[0];
					$b = $pair[1];
					
					$op = new Node;
					$op->kind = $node->kind;
					$op->callee = clone $node->callee;
					$op->range = clone $node->range;
					//$op->a_requiredTypes = clone $a->a_types;
					
					$aa = new Node;
					$aa->kind = 'expr.call.arg';
					$aa->expr = $a;
					$aa->range = clone $aa->expr->range;
					
					$ab = new Node;
					$ab->kind = 'expr.call.arg';
					$ab->expr = $b;
					$ab->range = clone $ab->expr->range;
					
					$op->args = array($aa, $ab);
					$node->exprs[] = $op;
				}
				
				unset($node->args);
				unset($node->callee);
				unset($node->a_functype);
				unset($node->a_target);
				$node->kind = 'expr.tuple';
				
				//$this->populateScope($node->a_scope, $node);
				$this->bind($node);
				$this->analyzeType($node);
				$this->lateBind($node);
			}
		}
	}
}
