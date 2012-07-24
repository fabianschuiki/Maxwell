<?php

class Entitializer
{
	protected $ast;
	protected $file;
	protected $entities;
	
	
	public function __construct(array $ast, Source\File $file)
	{
		$this->ast = $ast;
		$this->file = $file;
	}
	
	public function run()
	{
		$entities = array();
		$context = array();
		
		foreach ($this->ast as $node) {
			if ($node instanceof AST\Stmt\FuncDef) {
				$e = Entity\FunctionDefinition::makeFromSyntaxNode($node);
				if (isset($context['package'])) $e->setPackageName($context['package']);
				if ($e) $entities[] = $e;
			}
			if ($node instanceof AST\Stmt\Package) {
				$context['package'] = $node->getName();
			}
		}
		
		foreach ($entities as $e) {
			$e->setFile($this->file);
			$e->setSiblingEntities($entities);
		}
		
		$this->entities = $entities;
	}
	
	public function getEntities() { return $this->entities; }
}