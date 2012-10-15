<?php
namespace Analysis\Node;

/** Analysis information for the root entity. */
class RootEntity extends Node
{
	public $constraints;
	
	public function __construct(\Entity\Entity $entity)
	{
		parent::__construct($entity);
		$this->constraints = new \Analysis\ConstraintSet;
	}
}