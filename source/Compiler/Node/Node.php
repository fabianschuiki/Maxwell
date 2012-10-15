<?php
namespace Compiler\Node;

class Node
{
	static public function makeForEntity(\Entity\Entity $entity)
	{
		if ($entity instanceof \Entity\FunctionDefinition) return new FunctionDefinition($entity);
		if ($entity instanceof \Entity\TypeDefinition) return new TypeDefinition($entity);
		if ($entity instanceof \Entity\Expr\VarDef) return new VarDef($entity);
		if ($entity instanceof \Entity\Expr\Expr) return new Expr($entity);
		if ($entity instanceof \Entity\Type\Member) return new Member($entity);
		throw new \exception("Unable to make compiler node for ".vartype($entity));
	}
	
	protected $entity;
	
	public function __construct(\Entity\Entity $entity)
	{
		$this->entity = $entity;
	}
	
	public function getEntity() { return $this->entity; }
}