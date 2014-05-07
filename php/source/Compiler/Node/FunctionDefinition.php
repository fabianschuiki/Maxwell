<?php
namespace Compiler\Node;

class FunctionDefinition extends Node
{
	public function __construct(\Entity\FunctionDefinition $entity)
	{
		parent::__construct($entity);
	}
	
	protected $name;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
}