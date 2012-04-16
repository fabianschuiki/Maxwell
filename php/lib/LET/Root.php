<?php
namespace LET;

class Root extends Node
{
	public function __construct($ast = null)
	{
		assert(!$ast || is_array($ast));
		
		$this->scope = new Scope;
		
		if ($ast) {
			foreach ($ast as $node) {
				$n = Node::make($this->scope, $node);
				if (!$n instanceof Func_AST && !$n instanceof ConcreteType_AST) {
					global $issues;
					$issues[] = new \Issue(
						'warning',
						"{$node->nice()} is not allowed at file level. Ignored.",
						$node
					);
					return null;
				}
			}
		}
	}
	
	public function children()
	{
		return $this->scope->children();
	}
	
	public function details() { return null; }
}