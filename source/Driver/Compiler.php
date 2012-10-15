<?php
namespace Driver;
use Store\Manager;
use IssueList;
use Source\File;
use Entity;
use Compiler\CodePair;
use Compiler\Snippet;

class Compiler
{
	protected $entityIDs;
	
	public function __construct()
	{
		$this->entityIDs = array();
	}
	
	public function addEntityID($e) { $this->entityIDs[] = $e; }
	public function addEntityIDs(array $e) { $this->entityIDs = array_merge($this->entityIDs, $e); }
	public function getEntityIDs() { return $this->entityIDs; }
	
	public function run()
	{
		$manager = Manager::get();
		$entityStore = $manager->getEntityStore();
		$codeStore   = $manager->getCodeStore();
		
		$issues = new IssueList;
		$issues->push();
		
		$precompileIDs = $this->entityIDs;
		while (count($precompileIDs) && !$issues->isFatal())
		{
			//Fetch the entity we're supposed to precompile.
			$entityID = array_shift($precompileIDs);
			$entity = $entityStore->getEntity($entityID);
			echo "precompiling ".vartype($entity)."\n";
			
			//Decide the entity names.
			$this->decideEntityNames($entity);
		}
		
		$compileIDs = $this->entityIDs;
		while (count($compileIDs) && !$issues->isFatal())
		{
			//Fetch the entity we're supposed to compile.
			$entityID = array_shift($compileIDs);
			$entity = $entityStore->getEntity($entityID);
			echo "compiling ".vartype($entity)."\n";
			
			//Generate code.
			$pair = $this->generateRootCode($entity);
			$codeStore->persistCode($entityID, $pair);
		}
		
		$issues->pop();
		$issues->report();
	}
	
	/** Decides the name of individual entities, as it will appear in the C file. */
	private function decideEntityNames(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $c) {
			$this->decideEntityNames($c);
		}
		
		if ($entity instanceof Entity\Expr\VarDef) {
			$compiler = $entity->compiler;
			
			$type = $entity->analysis->type->inferred;
			$compiler->setName($entity->getName());
			$compiler->setType($type);
			
			//Decide what type of reference to use for this variable.
			if ($type instanceof \Type\Builtin) {
				$compiler->setRefType("local");
			}
			else if ($type instanceof \Type\Defined) {
				$compiler->setRefType("dynamic");
			}
			else {
				IssueList::add('error', "Variable '{$entity->getName()}' is of a type that cannot be compiled.", $entity);
			}
		}
		if ($entity instanceof Entity\TypeDefinition) {
			$compiler = $entity->compiler;
			$compiler->setLocalName("struct ".$entity->getName());
			$compiler->setName($entity->getName()."_t");
		}
	}
	
	static public function indent($str)
	{
		return "\t".str_replace("\n", "\n\t", $str);
	}
	
	private function generateRootCode(Entity\RootEntity $entity)
	{
		$snippet = new Snippet;
		if ($entity instanceof Entity\FunctionDefinition) {
			$declaration = "void ";
			$declaration .= $entity->getName();
			$declaration .= "(";
			$declaration .= ")";
			
			$block = $this->generateBlockCode($entity->getBody());
			
			$snippet->publicHeader .= "$declaration;\n";
			$snippet->stmts .= "$declaration\n{\n".static::indent(trim($block->stmts))."\n}\n";
		}
		if ($entity instanceof Entity\TypeDefinition) {
			$structName = $entity->compiler->getLocalName();
			$snippet->publicHeader = "typedef $structName {$entity->compiler->getName()};\n";
			$snippet->privateHeader = "$structName;\n";
			$snippet->stmts .= "$structName {\n};\n";
		}
		
		//Generate the header/source pair with the appropriate surroundings.
		$pair = new CodePair;
		$pair->header = "#pragma once\n\n".$snippet->publicHeader;
		
		//Include the headers of the known entities.
		$pair->source = "";
		foreach ($entity->getKnownEntities() as $e) {
			$pair->source .= "#include \"{$e->getID()}.h\"\n";
		}
		$pair->source .= "\n";
		if ($snippet->privateHeader) {
			$pair->source .= $snippet->privateHeader."\n";
		}
		$pair->source .= $snippet->stmts;
		
		return $pair;
	}
	
	private function generateBlockCode(Entity\Block $block)
	{
		$snippet = new Snippet;
		foreach ($block->getStmts() as $stmt) {
			$s = $this->generateStmtCode($stmt);
			$snippet->stmts .= $s->stmts;
		}
		return $snippet;
	}
	
	private function generateStmtCode(Entity\Stmt\Stmt $stmt)
	{
		$snippet = new Snippet;
		if ($stmt instanceof Entity\Stmt\Expr) {
			$s = $this->generateExprCode($stmt->getExpr());
			$snippet->stmts = $s->stmts;
			if ($s->expr && $s->exprRequired) $snippet->stmts .= $s->expr.";\n";
			$snippet->outerStmts = $s->outerStmts;
		}
		return $snippet;
	}
	
	private function generateExprCode(Entity\Expr\Expr $expr)
	{
		$snippet = new Snippet;
		if ($expr instanceof Entity\Expr\VarDef) {
			$type = $expr->compiler->getType();
			if ($type instanceof \Type\Builtin) {
				$typeName = $type->getName();
			}
			else if ($type instanceof \Type\Defined) {
				$typeName = $type->getDefinition()->compiler->getName();
			}
			if ($expr->compiler->getRefType() == "dynamic") {
				$typeName .= "*";
			}
			$expr->compiler->setCType($typeName);
			
			$stmt = "{$typeName} {$expr->compiler->getName()}";
			if ($i = $expr->getInitial()) {
				$is = $this->generateExprCode($i);
				$stmt .= " = {$is->expr}";
				$snippet->stmts .= $is->stmts;
			}
			$stmt .= ";\n";
			$snippet->stmts .= $stmt;
			$snippet->expr = "{$expr->compiler->getName()}";
		}
		if ($expr instanceof Entity\Expr\Operator\Binary) {
			$ls = $this->generateExprCode($expr->getLHS());
			$rs = $this->generateExprCode($expr->getRHS());
			$snippet->stmts .= $ls->stmts;
			$snippet->stmts .= $rs->stmts;
			$snippet->expr = "{$ls->expr} {$expr->getOperator()} {$rs->expr}";
			if ($expr->getOperator() == '=')
				$snippet->exprRequired = true;
		}
		if ($expr instanceof Entity\Expr\Constant) {
			$snippet->expr = $expr->getValue();
		}
		if ($expr instanceof Entity\Expr\Identifier) {
			$snippet->expr = $expr->analysis->binding->target->compiler->getName();
		}
		if ($expr instanceof Entity\Expr\MemberAccess) {
			$e = $this->generateExprCode($expr->getExpr());
			$snippet->stmts .= $e->stmts;
			$snippet->expr = "{$e->expr}->{$expr->getName()}";
		}
		if ($expr instanceof Entity\Expr\NewOp) {
			$type = $expr->analysis->type->inferred;
			if ($type instanceof \Type\Defined)
				$type = $type->getDefinition();
			$snippet->expr = "malloc(sizeof {$type->getName()})";
			$snippet->exprRequired = true;
		}
		return $snippet;
	}
}