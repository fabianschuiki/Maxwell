<?php
namespace Driver;
use Store\Manager;
use IssueList;
use Source\File;
use Entity;

class Analyzer
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
		
		$issues = new IssueList;
		$issues->push();
		
		while (count($this->entityIDs) && !$issues->isFatal())
		{
			//Fetch the entity we're supposed to analyze.
			$entityID = array_shift($this->entityIDs);
			$entity = $entityStore->getEntity($entityID);
			$entityStore->pushRootID($entityID);
			echo "loaded ".vartype($entity)."\n";
			
			//Bind all identifiers within type expressions and calculate the initial types of the entities.
			$this->bindIdentsInTypeExprs($entity);
			if ($issues->isFatal()) break;
			$this->calculateInitialType($entity);
			if ($issues->isFatal()) break;
			
			//Bind all identifiers that are left.
			$this->bindIdents($entity);
			if ($issues->isFatal()) break;
			
			//Don't spawn any constraints for now.
			//Spawn type constraints for the entities.
			//$this->spawnTypeConstraints($entity, $entity);
			
			//Calculate the required type.
			//$this->calculateRequiredType($entity);
			
			//Calculate the inferred types.
			$this->calculateInferredType($entity);
			
			//Store the entity back to disk.
			$entityStore->popRootID($entityID);
			$entityStore->persistEntity($entityID);
		}
		
		$issues->pop();
		$issues->report();
	}
	
	/** Concatenates the arguments into one output line, with the relevant entities highlighted. */
	static public function show()
	{
		$output = "";
		$ranges = array();
		foreach (func_get_args() as $arg) {
			if (is_string($arg)) {
				$output .= $arg." ";
			}
			if ($arg instanceof Entity\Expr\Identifier) {
				$output .= "'{$arg->getName()}' ";
				$ranges[] = $arg->getRange();
			}
			if ($arg instanceof Entity\Expr\VarDef) {
				$output .= "'{$arg->getName()}' ";
				$ranges[] = $arg->getHumanRange();
			}
			if ($arg instanceof \Type\Builtin) {
				$output .= "'{$arg->getName()}' ";
			}
		}
		$i = new \Issue('info', $output, $ranges);
		echo $i."\n";
	}
	
	/** Recursively binds all identifiers. */
	public function bindIdents(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\Identifier) {
			if (!$entity->analysis->binding->target) {
				//Try to bind the identifier to a builtin type.
				if (in_array($entity->getName(), \Type\Builtin::$names)) {
					$entity->analysis->binding->target = \Type\Builtin::makeWithName($entity->getName());
				}
				
				//Try to bind the identifier to something in scope.
				else {
					$scope = $entity->getScope();
					$result = null;
					while ($scope) {
						if ($scope instanceof Entity\Scope\ScopeDeclaration) {
							if ($scope->getDeclares()->getName() == $entity->getName()) {
								$result = $scope->getDeclares();
								break;
							}
						}
						if ($scope instanceof Entity\Scope\ScopeRoot) {
							foreach ($scope->getRootEntity()->getKnownEntities() as $e) {
								if ($e->getName() == $entity->getName()) {
									$result = $e;
									break;
								}
							}
							if ($result) break;
						}
						
						//Jump to the previous scope, or the outer scope if we're at the beginning.
						if ($s = $scope->getUpper())
							$scope = $s;
						else
							$scope = $scope->getOuter();
					}
					
					if ($result) {
						$entity->analysis->binding->target = $result;
					} else {
						IssueList::add('error', "Entity with name '{$entity->getName()}' is unknown.", $entity);
					}
				}
			}
		}
		else {
			foreach ($entity->getChildEntities() as $e)
				$this->bindIdents($e);
		}
	}
	
	/** Recursively binds all identifiers within type expressions like VarDefs. */
	public function bindIdentsInTypeExprs(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\VarDef) {
			if ($t = $entity->getType())    $this->bindIdents($t);
			if ($i = $entity->getInitial()) $this->bindIdentsInTypeExprs($i);
		}
		else {
			foreach ($entity->getChildEntities() as $e)
				$this->bindIdentsInTypeExprs($e);
		}	
	}
	
	/** Recursively calculates the initial type for each entity that does not yet have one set. */
	public function calculateInitialType(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->calculateInitialType($e);
		
		if (isset($entity->analysis->type) && !$entity->analysis->type->initial) {
			if ($entity instanceof Entity\Expr\VarDef) {
				$t = $entity->getType();
				if (!$t) {
					/*$entity->analysis->type->initial = \Type\Generic::make();
					static::show("variable", $entity, "has generic initial type");*/
					
					//For now, infer the type of the VarDef from its initial expression.
					if ($i = $entity->getInitial()) {
						if ($i->analysis->type->initial) {
							$entity->analysis->type->initial = $i->analysis->type->initial;
							//TODO: don't just reuse the type, actually make a copy of the type so now dependency arises.
						} else {
							IssueList::add('error', "Type of initial value of variable '{$entity->getName()}' cannot be inferred.", $i, $entity);
						}
					} else {
						IssueList::add('error', "Type of variable '{$entity->getName()}' cannot be inferred without an initial value.", $entity);
					}
				}
				else if ($t instanceof Entity\Expr\Identifier) {
					$tt = $t->analysis->binding->target;
					if ($tt instanceof \Type\Type) {
						$entity->analysis->type->initial = $tt;
					}
					else if ($tt instanceof \Entity\TypeDefinition) {
						$entity->analysis->type->initial = \Type\Defined::makeWithDefinition($tt);
					}
					else {
						IssueList::add('error', "Type '{$t->getName()}' is unknown.", $t->getRange());
					}
				}
				else {
					IssueList::add('error', "Not a valid type expression.", $t->getHumanRangeIfPossible());
				}
			}
			
			if ($entity instanceof Entity\Expr\Identifier) {
				if ($entity->analysis->binding->target) {
					if ($entity->analysis->binding->target instanceof \Type\Type) {
						$entity->analysis->type->initial = \Type\Builtin::makeWithName("Type");
					} else {
						$entity->analysis->type->initial = \Type\Generic::make();
					}
				} else {
					$entity->analysis->type->initial = \Type\Generic::make();
				}
			}
			
			if ($entity instanceof Entity\Expr\Constant) {
				switch ($entity->getType()) {
					case 'number': {
						$v = $entity->getValue();
						if (preg_match('/[.e]/', $v))
							$entity->analysis->type->initial = \Type\Builtin::makeWithName("float");
						else
							$entity->analysis->type->initial = \Type\Builtin::makeWithName("int");
					} break;
					case 'string': {
						$entity->analysis->type->initial = \Type\Builtin::makeWithName("String");
					} break;
				}
			}
		}
	}
	
	public function spawnTypeConstraints(Entity\RootEntity $root, Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->spawnTypeConstraints($root, $e);
		
		//Variable definitions have a type constraint between the initial expression and the type of the variable itself.
		if ($entity instanceof Entity\Expr\VarDef) {
			if ($i = $entity->getInitial()) {
				$root->analysis->constraints->add(\Analysis\Constraint::make($entity, $i));
			}
		}
		
		//Identifiers are supposed to have the same type as their target variable definitions.
		if ($entity instanceof Entity\Expr\Identifier) {
			if ($t = $entity->analysis->binding->target) {
				if ($t instanceof Entity\Expr\VarDef) {
					$root->analysis->constraints->add(\Analysis\Constraint::make($entity, $t));
				}
			}
		}
	}
	
	/** Recursively calculates the inferred type of the entity, based on constraints and the initial type. */
	public function calculateInferredType(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->calculateInferredType($e);
		
		if (isset($entity->analysis->type)) {
			$entity->analysis->type->inferred = $entity->analysis->type->initial;
			
			if ($entity instanceof Entity\Expr\Identifier) {
				$t = $entity->analysis->binding->target;
				if (isset($t->analysis->type)) {
					if ($tt = $t->analysis->type->inferred) {
						$entity->analysis->type->inferred = $tt;
					} else {
						IssueList::add('error', "Entity referenced by '{$entity->getName()}' has no valid type.", $t, $entity);
					}
				}
			}
			if ($entity instanceof Entity\Expr\Operator\Binary) {
				$lt = $entity->getLHS()->analysis->type->inferred;
				$rt = $entity->getRHS()->analysis->type->inferred;
				if ($lt && $rt) {
					if (\Type\Type::equal($lt, $rt)) {
						$entity->analysis->type->inferred = $lt;
					} else {
						IssueList::add('error', "Binary operator requires both operands to be of same type. Left operand is {$lt->toHumanReadableString()}, right operand is {$rt->toHumanReadableString()}.", $entity, array($entity->getLHS(), $entity->getRHS()));
					}
				}
			}
		}
	}
}