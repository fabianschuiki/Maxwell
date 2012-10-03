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
		
		//Fetch the entity we're supposed to analyze.
		$entityID = array_shift($this->entityIDs);
		$entity = $entityStore->getEntity($entityID);
		$entityStore->pushRootID($entityID);
		echo "loaded ".vartype($entity)."\n";
		
		//Bind all identifiers within type expressions and calculate the initial types of the entities.
		$this->bindIdentsInTypeExprs($entity);
		$this->calculateInitialType($entity);
		
		//Bind all identifiers that are left.
		$this->bindIdents($entity);
		
		//Store the entity back to disk.
		$entityStore->popRootID($entityID);
		$entityStore->persistEntity($entityID);
		
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
			//Try to bind the identifier to a builtin type.
			if (in_array($entity->getName(), \Type\Builtin::$names)) {
				$entity->analysis->binding->target = \Type\Builtin::makeWithName($entity->getName());
				static::show("identifier", $entity, "bound to builtin type");
			}
			
			//Try to bind the identifier to something in scope.
			else {
				$scope = $entity->getScope();
				$result = null;
				while ($scope) {
					if ($scope instanceof Entity\Scope\ScopeDeclaration && $scope->getDeclares()->getName() == $entity->getName()) {
						$result = $scope->getDeclares();
						break;
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
		
		if ($entity instanceof Entity\Expr\VarDef) {
			$t = $entity->getType();
			if (!$t) {
				$entity->analysis->type->initial = \Type\Generic::make();
				static::show("variable", $entity, "has generic initial type");
			}
			else if ($t instanceof Entity\Expr\Identifier) {
				$tt = $t->analysis->binding->target;
				if ($tt instanceof \Type\Type) {
					$entity->analysis->type->initial = $tt;
					static::show("variable", $entity, "has initial type", $tt);
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
					//use the target entity's type.
				}
			}
		}
	}
}