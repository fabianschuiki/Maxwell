<?php
namespace Compiler\Node;

class FuncArgument extends Node
{
	public function __construct(\Entity\Func\Argument $entity)
	{
		parent::__construct($entity);
		$this->type = new \Compiler\Type;
	}
	
	protected $name;
	
	public $type;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
}