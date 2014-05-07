<?php
namespace Analysis;

class ConstraintSet
{
	protected $pool;
	
	public function __construct()
	{
		$this->pool = array();
	}
	
	public function add(Constraint $c)
	{
		//echo "adding constraint {$c->describe()}\n";
		
		//Find the constraints to combine.
		$combine = array();
		foreach ($this->pool as $p) {
			foreach ($p->getEntities() as $e) {
				if ($c->containsEntity($e) && !in_array($p, $combine, true)) {
					$combine[] = $p;
					break;
				}
			}
		}
		
		//Calculate the new constraint.
		if (count($combine)) {
			$combine[] = $c;
			$entities = array();
			foreach ($combine as $cmb) {
				foreach ($cmb->getEntities() as $e) {
					if (!in_array($e, $entities, true)) {
						$entities[] = $e;
					}
				}
			}
			
			$c = Constraint::makeWithArray($entities);
			$pool = array();
			foreach ($this->pool as $p) {
				if (!in_array($p, $combine, true))
					$pool[] = $p;
			}
			$pool[] = $c;
			$this->pool = $pool;
			//echo "combined ".count($combine)." constraints to {$c->describe()}\n";
		}
		
		//If there's nothing to combine, simply add the constraint to the list.
		else {
			$this->pool[] = $c;
		}
	}
	
	public function getConstraints() { return $this->pool; }
}