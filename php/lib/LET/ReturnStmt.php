<?php
namespace LET;

class ReturnStmt extends Node
{
	public $asn;
	public $tuple;
	public $func;
	
	public function __construct(Scope $scope, \AST\ReturnStmt $node)
	{
		$tuple = Expr::make($scope, $node->expr);
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
		
		$this->asn   = $node;
		$this->tuple = $tuple;
		$this->func  = $func;
		$this->scope = $scope;
	}
	
	public function tuple()    { return $this->tuple; }
	public function children() { return array($this->tuple); }
	public function details()  { return "return {$this->tuple()->details()}"; }
	
	public function spawnConstraints(array &$constraints)
	{
		parent::spawnConstraints($constraints);
		
		$pairs = TypeTuple::fieldPairs(array_keys($this->tuple->fields), array_map(function($o){ return $o->name(); }, $this->func->outputs()));
		foreach ($pairs as $a => $b) {
			$output = null;
			foreach ($this->func->outputs() as $o) if ($o->name() == $b) $output = $o;
			$constraints[] = new EqualTypeConstraint($this->tuple->fields[$a], $output);
		}
	}
}