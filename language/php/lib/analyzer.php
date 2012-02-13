<?php
namespace Analyzer;

class Analyzer
{
	//The root block to be analyzed.
	protected $rootBlock;
	
	public function __construct($rootBlock) {
		$this->rootBlock = $rootBlock;
	}
	
	/** Analyzes the root block, extending its AST. */
	public function execute() {
		$this->rootBlock->a_scope = null;
		$this->applyScope($this->rootBlock);
		
		$this->inferType($this->rootBlock);
		
		print_r($this->rootBlock);
	}
	
	private function applyScope($node) {
		if ($node->kind == 'block') {
			$scope = new \stdClass;
			$scope->parent = $node->a_scope;
			$scope->names = array();
			$node->a_scope = $scope;
		}
		foreach ($node->nodes() as $n) {
			$n->a_scope = $node->a_scope;
			$this->applyScope($n);
		}
	}
	
	private function inferType($node) {
		foreach ($node->nodes() as $n) {
			$this->inferType($n);
		}
		switch ($node->kind) {
			case 'expr.const.num': $node->a_types = array('number'); break;
			case 'expr.op.binary': {
				if ($node->op->text == ':=') {
					$node->a_types = $node->rhs->a_types;
				} else {
					$node->a_types = array('combination of', $node->lhs->a_types, $node->rhs->a_types);
				}
			} break;
		}
	}
}
