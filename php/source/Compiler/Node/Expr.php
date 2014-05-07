<?php
namespace Compiler\Node;

class Expr extends Node
{
	public $type;
	
	public function __construct(\Entity\Expr\Expr $entity)
	{
		parent::__construct($entity);
		$this->type = new \Compiler\Type;
	}
}