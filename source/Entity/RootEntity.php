<?php
namespace Entity;

abstract class RootEntity extends Entity
{
	protected $file;
	protected $packageName;
	protected $siblingEntities;
	protected $knownEntities;
	protected $embeddedRootEntities;
	
	public $analysis;
	public $compiler;
	
	public function __construct()
	{
		$this->knownEntities = array();
		$this->analysis = \Analysis\Node\Node::makeForEntity($this);
		$this->compiler = \Compiler\Node\Node::makeForEntity($this);
	}
	
	public function setFile(\Source\File $file) { $this->file = $file; }
	public function getFile() { return $this->file; }
	
	public function setPackageName($packageName) { $this->packageName = $packageName; }
	public function getPackageName() { return $this->packageName; }
	
	public function setSiblingEntities(array $entities) { $this->siblingEntities = $entities; }
	public function getSiblingEntities() { return $this->siblingEntities; }
	
	public function setKnownEntities(array $entities) { $this->knownEntities = $entities; }
	public function getKnownEntities() { return $this->knownEntities; }
	
	public function setEmbeddedRootEntities(array $entities) { $this->embeddedRootEntities = $entities; }
	public function getEmbeddedRootEntities() { return $this->embeddedRootEntities; }
	
	public function pushID() { \Store\Manager::get()->getEntityStore()->pushRootID($this->getID()); }
	public function popID() { \Store\Manager::get()->getEntityStore()->popRootID($this->getID()); }

	public function copyInto(RootEntity $target)
	{
		$target->setFile($this->file);
		$target->setPackageName($this->packageName);
		$target->setSiblingEntities($this->siblingEntities);
		$target->setKnownEntities($this->knownEntities);
	}
}