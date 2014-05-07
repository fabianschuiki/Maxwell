<?php
namespace Compiler\Node;

class TypeDefinition extends Node
{
	public function __construct(\Entity\TypeDefinition $entity)
	{
		parent::__construct($entity);
	}
	
	protected $name;
	protected $localName;
	
	public function setName($n) { $this->name = $n; }
	public function getName() { return $this->name; }
	
	public function setLocalName($n) { $this->localName = $n; }
	public function getLocalName() { return $this->localName; }
}