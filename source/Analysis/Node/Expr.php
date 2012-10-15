<?php
namespace Analysis\Node;

/** Analysis information for expressions in general. */
class Expr extends Node
{
	public $type;
	
	public function __construct(\Entity\Entity $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
}