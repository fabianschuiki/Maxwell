<?php
namespace mwc;

class Entity
{
	public $id;
	public $basePath;
	public $node;
	
	public function __construct($id, $buildDir)
	{
		$this->id       = $id;
		$this->basePath = "$buildDir/$id";
	}
	
	public function letPath()       { return $this->basePath.".let"; }
	public function interfacePath() { return $this->basePath.".intf"; }
	
	public function save()
	{
		$pth = dirname($this->letPath())."/".str_replace('/', '<fwdslash>', array_pop($this->node->children())->details());
		
		$reduced = $this->node->reduceToInterface(new \LET\Scope);
		file_put_contents($this->interfacePath(), serialize($reduced));
		file_put_contents($pth.".intf.html", \Dump::let($reduced));
		
		$this->node->unbindFromInterfaces();
		file_put_contents($this->letPath(), serialize($this->node));
		file_put_contents($pth.".let.html", \Dump::let($this->node));
	}
	
	public function load()
	{
		$path = $this->letPath();
		if (!file_exists($path)) Driver::error("parsed LET should exist at '$path', but does not");
		$this->node = unserialize(file_get_contents($path));
		assert($this->node instanceof \LET\Func || $this->node instanceof \LET\ConcreteType);
	}
}