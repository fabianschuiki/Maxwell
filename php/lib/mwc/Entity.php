<?php
namespace mwc;

class Entity
{
	public $id;
	public $basePath;
	public $node;
	public $externalNodeIDs;
	
	public function __construct($id, $buildDir)
	{
		$this->id       = $id;
		$this->basePath = "$buildDir/entities/$id";
		$this->externalNodeIDs = array();
	}
	
	public function letPath()       { return $this->basePath.".let"; }
	public function interfacePath() { return $this->basePath.".intf"; }
	public function specsPath()     { return $this->basePath.".specs"; }
	public function externalsPath() { return $this->basePath.".extern"; }
	
	public function mainNode() { return array_pop($this->node->children()); }
	
	public function save()
	{
		$this->saveExternalNodeIDs();
		
		$apth = dirname($this->basePath)."/../debug/".str_replace('/', '<fwdslash>', array_pop($this->node->children())->details());
		/*$i = 0;
		do {
			$apth = $pth.".".$i;
			$i++;
		} while (file_exists($apth.".intf.html") || file_exists($apth.".let.html"));*/
		
		$reduced = $this->node->reduceToInterface(new \LET\Scope);
		file_put_contents($this->interfacePath(), serialize($reduced));
		file_put_contents($apth.".intf.html", \Dump::let($reduced));
		file_put_contents($apth.".let-nice.html", \Dump::let($this->node));
		
		$this->node->unbindFromInterfaces();
		file_put_contents($this->letPath(), serialize($this->node));
		file_put_contents($apth.".let.html", \Dump::let($this->node));
	}
	
	public function load(&$externalEntities, &$externalNodes, $additionalExternalNodeIDs = null)
	{
		$path = $this->letPath();
		if (!file_exists($path)) Driver::error("parsed LET should exist at '$path', but does not");
		$this->node = unserialize(file_get_contents($path));
		assert($this->node instanceof \LET\Root);
		global $issues;
		
		$this->loadExternalNodeIDs();
		if ($issues->dumpAndCheck()) return;
		
		$externalNodeIDs = $this->externalNodeIDs;
		if ($additionalExternalNodeIDs) $externalNodeIDs = array_merge($externalNodeIDs, $additionalExternalNodeIDs);
		$externalNodeIDs = array_unique(array_diff($externalNodeIDs, array($this->id)));
		
		//Import external nodes.
		$externalEntities = array();
		$externalNodes = array($this->id => $this->mainNode());
		foreach ($externalNodeIDs as $eid) {
			$e = new Entity($eid, dirname(dirname($this->basePath)));
			$e->loadInterface();
			$externalEntities[] = $e;
			$externalNodes[$eid] = $e->mainNode();
			Driver::debug("- imported $eid  {$e->mainNode()->desc()}");
		}
		foreach ($externalEntities as $entity) {
			$entity->node->bindProxies($externalNodes);
			$entity->node->reduce();
			
			$entity->node->bind();
			$entity->node->reduce();
		}
		if ($issues->dumpAndCheck()) return;
									
		$this->node->bindProxies($externalNodes);
		$this->node->reduce();
		if ($issues->dumpAndCheck()) return;
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
	
	public function saveExternalNodeIDs()
	{
		$ids = array();
		$this->node->gatherExternalNodeIDs($ids);
		$uids = array_unique(array_diff($ids, array($this->id)));
		file_put_contents($this->externalsPath(), serialize($uids));
	}
	
	public function loadExternalNodeIDs()
	{
		$path = $this->externalsPath();
		if (!file_exists($path)) return;
		$this->externalNodeIDs = unserialize(file_get_contents($path));
	}
}