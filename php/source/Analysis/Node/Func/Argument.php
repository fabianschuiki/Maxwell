<?php
namespace Analysis\Node\Func;

/** Analysis information for function definition arguments. */
class Argument extends \Analysis\Node\Node
{
	public $type;
	
	public function __construct(\Entity\Func\Argument $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
}