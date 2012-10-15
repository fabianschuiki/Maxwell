<?php
namespace Compiler\Node;

class Member extends Node
{
	public $type;
	
	public function __construct(\Entity\Type\Member $entity)
	{
		parent::__construct($entity);
		$this->type = new \Compiler\Type;
	}
}