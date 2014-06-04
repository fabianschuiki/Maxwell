<?php
namespace Analysis\Node\Call;

/** Analysis information for call arguments. */
class Argument extends \Analysis\Node\Node
{
	public $type;
	
	public function __construct(\Entity\Expr\Call\Argument $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
}