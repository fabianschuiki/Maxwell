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
			$this->calculateEntityNames($entity);
		}
		
		$compileIDs = $this->entityIDs;
		while (count($compileIDs) && !$issues->isFatal())
		{
			//Fetch the entity we're supposed to compile.
			$entityID = array_shift($compileIDs);
			$entity = $entityStore->getEntity($entityID);
			echo "compiling ".vartype($entity)."\n";
			
			//Prepare entity type information.
			$this->calculateEntityTypes($entity);
			
			//Generate code.
			$pair = $this->generateRootCode($entity);
			$codeStore->persistCode($entityID, $pair);
		}
		
		$issues->pop();
		$issues->report();
	}
	
	/** Calculates the name of individual entities, as it will appear in the C file. */
	private function calculateEntityNames(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $c) {
			$this->calculateEntityNames($c);
		}
		
		if ($entity instanceof Entity\Expr\VarDef) {
			$entity->compiler->setName($entity->getName());
		}
		if ($entity instanceof Entity\TypeDefinition) {
			$compiler = $entity->compiler;
			$compiler->setLocalName("struct ".$entity->getName());
			$compiler->setName($entity->getName()."_t");
		}
		if ($entity instanceof Entity\Type\Member) {
			$compiler = $entity->compiler;
			$compiler->setName($entity->getName());
		}
		if ($entity instanceof Entity\FunctionDefinition) {
			$compiler = $entity->compiler;
			$compiler->setName($entity->getName());
		}
		if ($entity instanceof Entity\Func\Argument) {
			$entity->compiler->setName($entity->getName());
		}
	}
	
	private function calculateEntityTypes(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $c) {
			$this->calculateEntityTypes($c);
		}
		
		if ($entity instanceof Entity\Expr\Expr) {
			$compiler = $entity->compiler;
			$type = $entity->analysis->type->inferred;
			
			if ($type instanceof \Type\Builtin) {
				$compiler->type->setName($type->getName());
				$compiler->type->setPointerLevel(0);
			}
			else if ($type instanceof \Type\Defined) {
				$compiler->type->setName($type->getDefinition()->compiler->getName());
				$compiler->type->setPointerLevel(1);
			}
			else {
				//throw new \exception("Type of ".vartype($entity)." cannot be compiled");
			}
		}
		if ($entity instanceof Entity\Type\Member || $entity instanceof Entity\Func\Argument) {
			$compiler = $entity->compiler;
			$type = $entity->analysis->type->inferred;
			if ($type instanceof \Type\Builtin) {
				$compiler->type->setName($type->getName());
				$compiler->type->setPointerLevel(0);
			}
			else if ($type instanceof \Type\Defined) {
				$compiler->type->setName($type->getDefinition()->compiler->getName());
				$compiler->type->setPointerLevel(1);
			}
			else {
				throw new \exception("Type of ".vartype($entity)." cannot be compiled");
			}
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
			$output = $entity->getOutputArgs()->getArgs();
			if (count($output) > 1) {
				throw new \exception("Trying to compile function with more than one return value.");
			}
			if (count($output) == 0) {
				$declaration = "void ";
			} else {
				$declaration = $output[0]->compiler->type->getCType()." ";
			}
			$declaration .= $entity->getName();
			$declaration .= "(";
			
			$args = array();
			foreach ($entity->getInputArgs()->getArgs() as $arg) {
				$args[] = "{$arg->compiler->type->getCType()} {$arg->compiler->getName()}";
			}
			$declaration .= implode(", ", $args);
			
			$declaration .= ")";
			
			$block = $this->generateBlockCode($entity->getBody());
			
			$snippet->publicHeader .= "$declaration;\n";
			$snippet->stmts .= "$declaration\n{\n".static::indent(trim($block->stmts))."\n}\n";
		}
		if ($entity instanceof Entity\TypeDefinition) {
			$structName = $entity->compiler->getLocalName();
			$snippet->publicHeader = "typedef $structName {$entity->compiler->getName()};\n";
			$snippet->privateHeader = "$structName;\n";
			
			$body = "";
			foreach ($entity->getMembers() as $member) {
				$body .= "\t{$member->compiler->type->getCType()} {$member->compiler->getName()};\n";
			}
			
			$snippet->stmts .= "$structName {\n$body};\n";
		}
		
		$preamble = "/* This file was automatically generated by the Maxwell compiler. */";
		
		//Generate the header/source pair with the appropriate surroundings.
		$pair = new CodePair;
		$pair->header = "$preamble\n#pragma once\n\n".$snippet->publicHeader;
		
		//Include the headers of the known entities.
		$pair->source = "$preamble\n#include \"{$entity->getID()}.h\"\n\n";
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
		else if ($stmt instanceof Entity\Stmt\IfStmt) {
			$condition = $this->generateExprCode($stmt->getCondition());
			$block = $this->generateBlockCode($stmt->getBody());
			$snippet->stmts = $condition->stmts;
			$snippet->stmts .= "if ({$condition->expr}) {\n".static::indent(trim($block->stmts))."\n}";
			if ($else = $stmt->getElse()) {
				$elseCode = $this->generateStmtCode($else);
				$snippet->stmts .= " ".$elseCode->stmts;
			} else {
				$snippet->stmts .= "\n";
			}
		}
		else if ($stmt instanceof Entity\Stmt\ElseStmt) {
			$block = $this->generateBlockCode($stmt->getBody());
			$snippet->stmts = "else {\n".static::indent(trim($block->stmts))."\n}\n";
		}
		else {
			throw new \exception("Unable to generate statement code for ".vartype($stmt));
		}
		return $snippet;
	}
	
	private function generateExprCode(Entity\Expr\Expr $expr)
	{
		$snippet = new Snippet;
		if ($expr instanceof Entity\Expr\VarDef) {
			$stmt = "{$expr->compiler->type->getCType()} {$expr->compiler->getName()}";
			if ($i = $expr->getInitial()) {
				$is = $this->generateExprCode($i);
				$stmt .= " = {$is->expr}";
				$snippet->stmts .= $is->stmts;
			}
			$stmt .= ";\n";
			$snippet->stmts .= $stmt;
			$snippet->expr = "{$expr->compiler->getName()}";
		}
		else if ($expr instanceof Entity\Expr\Operator\Binary) {
			$ls = $this->generateExprCode($expr->getLHS());
			$rs = $this->generateExprCode($expr->getRHS());
			$snippet->stmts .= $ls->stmts;
			$snippet->stmts .= $rs->stmts;
			$snippet->expr = "{$ls->expr} {$expr->getOperator()} {$rs->expr}";
			if ($expr->getOperator() == '=')
				$snippet->exprRequired = true;
		}
		else if ($expr instanceof Entity\Expr\Constant) {
			$snippet->expr = $expr->getValue();
		}
		else if ($expr instanceof Entity\Expr\Identifier) {
			$snippet->expr = $expr->analysis->binding->target->compiler->getName();
		}
		else if ($expr instanceof Entity\Expr\MemberAccess) {
			$e = $this->generateExprCode($expr->getExpr());
			$op = ($expr->getExpr()->compiler->type->getPointerLevel() > 0 ? "->" : ".");
			$snippet->stmts .= $e->stmts;
			$snippet->expr = "{$e->expr}$op{$expr->getName()}";
		}
		else if ($expr instanceof Entity\Expr\NewOp) {
			$snippet->expr = "malloc(sizeof *({$expr->compiler->type->getCType()}))";
			$snippet->exprRequired = true;
		}
		else if ($expr instanceof Entity\Expr\Call) {
			$func = $expr->getCallee()->analysis->binding->target;
			$name = $func->compiler->getName();
			$args = array();
			foreach ($func->getInputArgs()->getArgs() as $i => $arg) {
				echo "- processing input arg {$arg->getName()}\n";
				$callArg = null;
				foreach ($expr->getArgs()->getArgs() as $a) {
					if ($a->getName() == $arg->getName()) {
						$callArg = $a;
						break;
					}
				}
				if (!$callArg) {
					$callArgs = $expr->getArgs()->getArgs();
					if ($i < count($callArgs)) {
						$callArg = $callArgs[$i];
					} else {
						IssueList::add('error', "Function call is lacking argument '{$arg->getName()}'.", $expr, $arg);
					}
				}
				$as = $this->generateExprCode($callArg->getExpr());
				$snippet->stmts .= $as->stmts;
				$args[] = $as->expr;
			}
			$snippet->expr = "$name(".implode(", ", $args).")";
			$snippet->exprRequired = true;
		}
		else {
			throw new \exception("Unable to generate expression code for ".vartype($expr));
		}
		return $snippet;
	}
}