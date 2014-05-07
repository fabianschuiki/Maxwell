<?php
namespace Analysis\Node;

/** Analysis information for function definitions. */
class FunctionDefinition extends RootEntity
{
	public $type;
	
	public function __construct(\Entity\FunctionDefinition $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
}