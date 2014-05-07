<?php
namespace Analysis\Node;

/** Analysis information for expressions in general. */
class Identifier extends Expr
{
	public $binding;
	
	public function __construct(\Entity\Entity $entity)
	{
		parent::__construct($entity);
		$this->binding = new \Analysis\Binding;
	}
}