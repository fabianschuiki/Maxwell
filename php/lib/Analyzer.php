<?php

class Analyzer
{
	public $nodes;
	public $importScope;
	public $scope;
	public $issues;
	
	public function run()
	{
		//Prepare the builtin types and functions.
		$builtin = $this->buildBuiltinScope();
		
		//Build the initial Language Entity Tree.
		$scope = new LET\Scope($builtin);
		$this->scope = $scope;
		foreach ($this->nodes as $node) {
			$this->buildEntity($scope, $node);
		}
		foreach ($scope->children() as $node) $node->clearConstraints();
		if ($this->issues->isFatal()) return;
		
		//Analysis is an iterative process that works on a bunch of nodes at a time.
		$nodes = $scope->children();
		$wdc = 0;
		while ($nodes)
		{
			//Bind the identifiers where possible.
			$this->bind($nodes);
			$this->reduce($nodes);
			if ($this->issues->isFatal()) return;
		
			//Infer types.
			$this->inferTypes($nodes);
			$this->reduce($nodes);
			if ($this->issues->isFatal()) return;
		
			//Build the specializations.
			$specializations = $this->buildSpecializations($nodes);
			echo "built ".count($specializations)." specializations\n";
			if ($this->issues->isFatal()) return;
			
			//The specializations need to be analyzed as well.
			$nodes = $scope->children();
			if (!$specializations) break;
			
			if ($wdc++ > 100) {
				trigger_error("Analyzer ran through $wdc iterations, which is quite unlikely to happen.", E_USER_ERROR);
			}
			//letDumpNPause();
		}
		
		//Complain about ambiguities.
		//$this->complainAboutAmbiguities($scope->children());
	}
	
	private function buildBuiltinScope()
	{
		$scope = new LET\Scope;
		
		$primitives = array('int', 'float');
		foreach ($primitives as $primitive) {
			new LET\PrimitiveBuiltinType($scope, $primitive);
		}
		
		return $scope;
	}
	
	private function buildEntity(LET\Scope $scope, AST\Node $node)
	{
		switch ($node->kind()) {
			case 'TypeStmt': new LET\ConcreteType_AST($scope, $node); break;
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
	
	public function __call($name, $args)
	{
		if (count($args) >= 1 && is_array($args[0])) {
			foreach ($args[0] as $node)	call_user_func_array(array($node, $name), array_slice($args, 1));
			return;
		}
		trigger_error("Analyzer does not know function $name for ".implode(', ', $args). ".", E_USER_ERROR);
	}
	
	private function spawnConstraints(array $nodes)
	{
		$constraints = array();
		foreach ($nodes as $node) {
			$node->spawnConstraints($constraints);
		}
		
		$reduced = array();
		foreach ($constraints as $a) {
			$kind = $a->kind();
			$merged = false;
			foreach ($reduced as $b) {
				if ($kind != $b->kind()) continue;
				if ($b->merge($a)) {
					$merged = true;
					break;
				}
			}
			if (!$merged) $reduced[] = $a;
		}
		
		return $reduced;
	}
	
	private function inferTypes(array $nodes)
	{
		$constraints = $this->spawnConstraints($nodes);
		foreach ($constraints as $c) echo "unordered constraint {$c->details()}\n";
		
		foreach ($nodes as $node) $node->clearConstraints();
		while (count($constraints) > 0) {
			usort($constraints, function($a,$b) {
				$as = $a->isSpecific();
				$bs = $b->isSpecific();
				if ($as && !$bs) return -1;
				if (!$as && $bs) return  1;
				return $a->dependency($b);
			});
			
			$constraint = array_shift($constraints);
			echo "\033[1;35mconstraint\033[0m {$constraint->details()} ".($constraint->isSpecific() ? '<specific!>' : '')."\n";
			$constraint->impose();
		}
	}
	
	private function buildSpecializations(array $nodes)
	{
		$specializations = array();
		foreach ($nodes as $node) {
			$node->buildSpecializations($specializations);
		}
		return array_unique($specializations, SORT_REGULAR);
	}
}
