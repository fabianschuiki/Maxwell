<?php
namespace Analysis\Node\Call;

/** Analysis information for call argument tuples. */
class Tuple extends \Analysis\Node\Node
{
	public $type;
	
	public function __construct(\Entity\Expr\Call\Tuple $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
}