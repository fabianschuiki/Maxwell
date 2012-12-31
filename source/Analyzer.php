<?php

class Analyzer
{
	public $nodes;
	public $importScope;
	public $scope;
	public $root;
	public $issues;
	public $entities;
	
	public $finalize = true;
	public $restrictRootLevel = true;
	
	static public $stat_imposeTypeConstraint = 0;
	static public $stat_notifyNodeChangedType = 0;
	static public $stat_maybeTypeChanged = 0;
	static public $stat_bind = 0;
	static public $stat_bindInVain = 0;
	static public $stat_reimposedConstraints = 0;
	
	//static public $stat_time_impose = 0;
	static public $stat_time_sortingConstraints = 0;
	static public $stat_time_initialSortingConstraints = 0;
	static public $stat_time_constraintIsSpecificMapping = 0;
	static public $stat_time_constraintIsSpecificIteration = 0;
	static public $stat_time_calculateUnconstrainedType = 0;
	
	static public function dumpStats($offsets = null)
	{
		foreach (get_class_vars(Analyzer) as $key => $value) {
			if (strpos($key, "stat_") !== 0) continue;
			if (is_array($value)) continue;
			$n = substr($key, 5);
			$v = $value;
			if (is_array($offsets)) $v -= $offsets[$key];
			if (strpos($n, "time_") === 0) $v = sprintf('%.1fms', $v*1000);
			echo "- ".$n.":  ".($v)."\n";
		}
	}
	
	public function run()
	{
		assert($this->root instanceof \LET\Root);
		//Prepare the builtin types and functions.
		//$builtin = $this->buildBuiltinScope();
		
		//Build the root node and scope.
		/*$root = $this->root;
		if (!$root) {
			$scope = new LET\Scope($builtin);
			$root = new LET\RootNode($scope);
		}
		$this->root = $root;
		$scope = $root->scope;
		$this->scope = $scope;
		
		//Build the initial Language Entity Tree.
		$nodes = array();
		foreach ($this->nodes as $node) {
			$stmt = $this->buildEntity($scope, $node);
			if ($stmt instanceof LET\Node) {
				if (!$stmt instanceof LET\Func_AST && !$stmt instanceof LET\ConcreteType_AST) $root->stmts[] = $stmt;
			}
		}
		$nodes = array_merge($scope->children(), $root->stmts);*/
		
		$scope = $this->root->scope;
		$nodes = $this->root->children();
		$this->entities = $nodes;
		if ($this->issues->isFatal()) return;
		
		//Analysis is an iterative process that works on a bunch of nodes at a time.
		$wdc = 0;
		while ($nodes)
		{
			//Bind the identifiers where possible.
			$this->bind($nodes);
			$this->reduce($nodes);
			if ($this->issues->isFatal()) return;
			//letDumpNPause();
		
			//Infer types.
			$this->inferTypes($nodes);
			//$this->reduce($nodes);
			if ($this->issues->isFatal()) return;
			//letDumpNPause();
		
			//Build the specializations.
			$specializations = $this->buildSpecializations($this->root->children());
			//mwc\debug("built ".count($specializations)." specializations\n");
			if ($this->issues->isFatal()) return;
			//letDumpNPause();
			
			//The specializations need to be analyzed as well.
			$nodes = /*$scope->children()*/$specializations;
			if (!$specializations) break;
			
			if ($wdc++ > 100) {
				trigger_error("Analyzer ran through $wdc iterations, which is quite unlikely to happen.", E_USER_ERROR);
			}
		}
		
		/*if ($this->finalize) {
			//Strip the generics from the scope.
			//NOTE: Comment this line to see the generic nodes for debugging.
			$scope->stripGenerics();
		
			//Complain about ambiguities.
			//NOTE: Comment this line if not stripping generics as they will be whining about how they are ambiguous.
			$this->complainAboutAmbiguities($this->root->children());
		}*/
	}
	
	public function __call($name, $args)
	{
		if (count($args) >= 1 && is_array($args[0])) {
			//mwc\debug("-> \033[32;1m{$name}\033[0m\n");
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
		//mwc\debug("-> \033[32;1minferTypes\033[0m\n");
		
		$constraints = $this->spawnConstraints($nodes);
		//foreach ($constraints as $c) echo "unordered constraint {$c->details()}\n";
		
		//Sort the constraints so they are applied correctly.
		$t0 = microtime(true);
		usort($constraints, function($a,$b) {
			/*$as = $a->isSpecific();
			$bs = $b->isSpecific();
			if ($as && !$bs) return -1;
			if (!$as && $bs) return  1;*/
			return $a->dependency($b);
		});
		\Analyzer::$stat_time_initialSortingConstraints += microtime(true)-$t0;
		
		foreach ($nodes as $node) $node->clearConstraints();
		$left = $constraints;
		while (count($left) > 0) {
			$stat = get_class_vars(Analyzer);
			$t0 = microtime(true);
			usort($left, function($a,$b) {
				$as = $a->isSpecific();
				$bs = $b->isSpecific();
				if ($as && !$bs) return -1;
				if (!$as && $bs) return  1;
				//return $a->dependency($b);
				return 0;
			});
			\Analyzer::$stat_time_sortingConstraints += microtime(true)-$t0;
			
			$constraint = array_shift($left);
			$constraint->impose();
			
			//self::dumpStats($stat);
			
			if (count($left) == 0) {
				foreach ($constraints as $constraint) {
					if ($constraint->imposeAgain) {
						$constraint->imposeAgain = false;
						if ($constraint->met()) continue;
						mwc\debug("\033[1;35mre-imposing\033[0m {$constraint->details()}\n");
						array_push($left, $constraint);
					}
				}
			}
		}
	}
	
	private function buildSpecializations(array $nodes)
	{
		//mwc\debug("-> \033[32;1mbuildSpecializations\033[0m\n");
		
		$specializations = array();
		foreach ($nodes as $node) {
			$node->buildSpecializations($specializations);
		}
		return /*array_unique(*/$specializations/*, SORT_REGULAR)*/;
	}
}