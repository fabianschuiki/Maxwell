<?php

class Analyzer
{
	public $nodes;
	public $issues;
	
	public function run()
	{
		$this->issues = array();
		$rootScope = new Scope;
		foreach ($this->nodes as $n) {
			$this->analyzeScopes($n, $rootScope);
			$this->analyzeTypes($n);
		}
		foreach ($this->issues as $i) {
			echo "$i\n";
		}
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
				case 'def.func': $parent->names[$node->name->text] = $node; break;
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
			if (!isset($node->requiredType)) {
				$node->requiredType = new Type;
			}
			switch ($node->kind) {
				case 'expr.const.numeric': $node->possibleType = new Type('int', 'float'); break;
				case 'expr.const.string':  $node->possibleType = new Type('string'); break;
				case 'expr.var':           $node->possibleType = new Type($node->datatype->text); break;
				case 'expr.op.binary': {
					$this->analyzeTypes($node->lhs);
					$this->analyzeTypes($node->rhs);
					
					$node->possibleType = $node->lhs->type->intersection($node->rhs->type);
					$node->lhs->requiredType = $node->possibleType;
					$node->rhs->requiredType = $node->possibleType;
					
					$this->analyzeTypes($node->lhs);
					$this->analyzeTypes($node->rhs);
					
					if (!count($node->possibleType->types)) {
						$this->issues[] = "{$node->op->range}: binary operator requires both sides to be of equal type, which is impossible for {$node->lhs->possibleType} and {$node->rhs->possibleType}";
					}
				} break;
				case 'expr.ident': {
					if ($node->target) {
						$node->possibleType = $node->target->type;
					}
				} break;
				default: $node->possibleType = new Type; break;
			}
			$node->type = $node->possibleType->intersection($node->requiredType);
		} else {
			if (isset($node->nodes)) {
				foreach ($node->nodes as $n) {
					$this->analyzeTypes($n);
				}
			}
		}
	}
}
