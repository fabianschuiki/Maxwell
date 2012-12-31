<?php
namespace Analysis\Node\Func;

/** Analysis information for function definition argument tuples. */
class Tuple extends \Analysis\Node\Node
{
	public $type;
	
	public function __construct(\Entity\Func\Tuple $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
}