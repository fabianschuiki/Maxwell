<?php
namespace LET;

class Root extends Node
{
	public $imports;
	public $importedRoots;
	public $specializations;
	
	public function __construct($ast = null)
	{
		assert(!$ast || is_array($ast));
		
		$this->scope  = new Scope(null, $this);
		$this->imports = array();
		$this->specializations = array();
		
		if ($ast) {
			foreach ($ast as $node) {
				if ($node instanceof \AST\ImportStmt) {
					$this->imports[] = $node;
					continue;
				}
				
				$n = Node::make($this->scope, $node);
				if (!$n instanceof Func_AST && !$n instanceof ConcreteType_AST) {
					global $issues;
					$issues[] = new \Issue(
						'warning',
						"{$node->nice()} is not allowed at file level. Ignored.",
						$node
					);
				}
			}
		}
	}
	
	public function children() { return $this->scope->children(); }
	public function details()  { return null; }
	
	public function reduceToInterface()
	{
		$scope   = $this->scope->reduceToInterface();
		$imports = $this->imports;
		
		$r = new self;
		$r->imports  = $imports;
		$r->scope    = $scope;
		$scope->node = $r;
		return $r;
	}
}