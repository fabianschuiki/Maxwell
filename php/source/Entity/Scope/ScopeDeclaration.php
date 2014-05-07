<?php
namespace Entity\Scope;

class ScopeDeclaration extends Scope
{
	protected $declares;
	
	public function setDeclares(\Entity\Entity $e) { $this->declares = $e; }
	public function getDeclares() { return $this->declares; }
}