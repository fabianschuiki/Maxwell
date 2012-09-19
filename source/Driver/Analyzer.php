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
		
		$issues = new IssueList;
		$issues->push();
		
		//Fetch the entity we're supposed to analyze.
		$entityID = array_shift($this->entityIDs);
		$entity = $manager->getEntityStore()->getEntity($entityID);
		echo "loaded ".vartype($entity)."\n";
		$this->initAnalysisNodes($entity);
		
		$issues->pop();
		$issues->report();
	}
	
	/** Recursively creates the initial analysis nodes for the given entity where they are missing. */
	public function initAnalysisNodes(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr) {
			echo "would init analysis node on ".vartype($entity)."\n";
		}
		
		if ($entity instanceof Entity\FunctionDefinition) {
			$this->initAnalysisNodes($entity->getBody());
		}
		else if ($entity instanceof Entity\Block) {
			foreach ($entity->getStmts() as $stmt)
				$this->initAnalysisNodes($stmt);
		}
	}
}