<?php
namespace Entity;

class RootEntity extends Entity
{
	protected $file;
	protected $packageName;
	protected $siblingEntities;
	protected $knownEntities;
	
	public function __construct()
	{
		$this->knownEntities = array();
	}
	
	public function setFile(\Source\File $file) { $this->file = $file; }
	public function getFile() { return $this->file; }
	
	public function setPackageName(\Lexer\Token $packageName) { $this->packageName = $packageName; }
	public function getPackageName() { return $this->packageName; }
	
	public function setSiblingEntities(array $entities) { $this->siblingEntities = $entities; }
	public function getSiblingEntities() { return $this->siblingEntities; }
	
	public function setKnownEntities(array $entities) { $this->knownEntities = $entities; }
	public function getKnownEntities() { return $this->knownEntities; }
	
	public function pushID() { \Store\Manager::get()->getEntityStore()->pushRootID($this->getID()); }
	public function popID() { \Store\Manager::get()->getEntityStore()->popRootID($this->getID()); }
}