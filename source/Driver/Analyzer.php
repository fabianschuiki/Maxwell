<?php
namespace Driver;
use Store\Manager;
use IssueList;
use Source\File;

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
		
		$issues->pop();
		$issues->report();
	}
}