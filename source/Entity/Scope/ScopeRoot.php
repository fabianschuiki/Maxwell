<?php
namespace Entity\Scope;

class ScopeRoot extends Scope
{
	protected $rootEntity;
	
	public function setRootEntity(\Entity\RootEntity $e) { $this->rootEntity = $e; }
	public function getRootEntity() { return $this->rootEntity; }
}