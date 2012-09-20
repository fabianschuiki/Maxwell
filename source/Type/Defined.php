<?php
namespace Type

class Defined extends Type
{
	protected $typeDef;
	
	public function setTypeDef(\Entity\TypeDefinition $d) { $this->typeDef = $d; }
	public function getTypeDef() { return $this->typeDef; }
}