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
	public function specsPath()     { return $this->basePath.".specs"; }
	
	public function save()
	{
		$pth = dirname($this->letPath())."/".str_replace('/', '<fwdslash>', array_pop($this->node->children())->details());
		$i = 0;
		do {
			$apth = $pth.".".$i;
			$i++;
		} while (file_exists($apth.".intf.html") || file_exists($apth.".let.html"));
		
		$reduced = $this->node->reduceToInterface(new \LET\Scope);
		file_put_contents($this->interfacePath(), serialize($reduced));
		file_put_contents($apth.".intf.html", \Dump::let($reduced));
		file_put_contents($apth.".let-nice.html", \Dump::let($this->node));
		
		$this->node->unbindFromInterfaces();
		file_put_contents($this->letPath(), serialize($this->node));
		file_put_contents($apth.".let.html", \Dump::let($this->node));
	}
	
	public function load()
	{
		$path = $this->letPath();
		if (!file_exists($path)) Driver::error("parsed LET should exist at '$path', but does not");
		$this->node = unserialize(file_get_contents($path));
		assert($this->node instanceof \LET\Root);
	}
	
	public function loadInterface()
	{
		$path = $this->interfacePath();
		if (!file_exists($path)) Driver::error("interface should exist at '$path', but does not");
		$this->node = unserialize(file_get_contents($path));
		assert($this->node instanceof \LET\Root);
	}
	
	public function loadSpecs()
	{
		$path = $this->specsPath();
		if (!file_exists($path)) return;
		$this->node->specializations = unserialize(file_get_contents($path));
		assert(is_array($this->node->specializations));
	}
	
	public function saveSpecs()
	{
		file_put_contents($this->specsPath(), serialize($this->node->specializations));
	}
}