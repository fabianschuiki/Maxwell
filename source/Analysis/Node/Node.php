<?php
namespace Analysis\Node;

/** Root class for analysis nodes assigned to entities. */
class Node
{
	static public function makeForEntity(\Entity\Entity $e)
	{
		if ($e instanceof \Entity\Expr\Identifier) return new Identifier($e);
		else if ($e instanceof \Entity\Expr\Expr)  return new Expr($e);
		else if ($e instanceof \Entity\Type\Member)  return new Expr($e);
		else if ($e instanceof \Entity\RootEntity) return new RootEntity($e);
		
		throw new \exception("Unable to make analysis node for ".vartype($e));
	}
	
	public $entity;
	
	public function __construct(\Entity\Entity $entity)
	{
		$this->entity = $entity;
	}
}