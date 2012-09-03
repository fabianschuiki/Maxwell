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
			$e = null;
			if ($node instanceof AST\Stmt\FuncDef) {
				$e = Entity\FunctionDefinition::makeFromSyntaxNode($node);
				if ($e) $entities[] = $e;
			}
			else if ($node instanceof AST\Stmt\TypeDef) {
				$e = Entity\TypeDefinition::makeFromSyntaxNode($node);
				if ($e) $entities[] = $e;
			}
			else if ($node instanceof AST\Stmt\Package) {
				$context['package'] = $node->getName();
			}
			else {
				IssueList::add('warning', "Unable to wrap statement into a language entity.", $node->getRange());
			}
			
			if ($e && isset($context['package'])) $e->setPackageName($context['package']);
		}
		
		foreach ($entities as $e) {
			$e->setFile($this->file);
			$e->setSiblingEntities($entities);
		}
		
		$this->entities = $entities;
	}
	
	public function getEntities() { return $this->entities; }
}