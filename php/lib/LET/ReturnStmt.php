<?php
namespace LET;

class ReturnStmt extends Stmt
{
	public $tuple;
	public $func;
	public $pairs;
	
	public function __construct(Scope $scope, Expr $expr)
	{
		$tuple = $expr;
		if (!$tuple instanceof Tuple) $tuple = new Tuple_Impl($scope, array($tuple));
		
		$func = $scope;
		while ($scope) {
			if ($scope->node instanceof Func) {
				$func = $scope->node;
				break;
			}
			$scope = $scope->outer;
		}
		if (!$func) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Return must be somewhere in a function body.",
				$this
			);
		}
		
		$pairs = array();
		if ($func) {
			$pairs = TypeTuple::fieldPairs(array_keys($tuple->fields), array_map(function($o){ return $o->name(); }, $func->outputs()));
			$hasOutputs = count($func->outputs()) > 0;
			foreach ($tuple->fields as $name => $expr) {
				if (!isset($pairs[$name])) {
					if ($hasOutputs) {
						global $issues;
						$issues[] = new \Issue(
							'warning',
							"Return value ignored as it does not have a corresponding function output argument.",
							$expr
						);
					} else {
						$n = $name;
						if (is_numeric($n)) {
							for ($i = 0; $i < 1000 && $n == null; $i++) {
								$n = "~$i";
								foreach ($func->outputs() as $o) {
									if ($o->name() == $n) {
										$n = null;
										break;
									}
								}
							}
						}
						
						$arg = new FuncArg_Impl($func->subscope, new GenericType, $n);
						$arg->parent = $func;
						$func->outputs[] = $arg;
						$pairs[$name] = $arg;
						echo "create function output argument {$arg->desc()}\n";
					}
				} else {
					foreach ($func->outputs() as $o) if ($o->name() == $name) $pairs[$name] = $o;
				}
			}
		}
		
		$this->tuple = $tuple;
		$this->func  = $func;
		$this->pairs = $pairs;
		$this->scope = $scope;
	}
	
	public function children() { return array($this->tuple); }
	public function details()  { return "return {$this->tuple->details()}"; }
	
	public function spawnConstraints(array &$constraints)
	{
		parent::spawnConstraints($constraints);
		
		foreach ($this->pairs as $a => $b) {
			$constraints[] = new EqualTypeConstraint($this->tuple->fields[$a], $b);
		}
	}
	
	public function cloneInto(Scope $scope)
	{
		return new self($scope, $this->tuple->cloneInto($scope));
	}
}