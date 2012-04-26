<?php
namespace LET;

class ConcreteType_Proxy extends ConcreteType
{
	public $resolved;
	
	public function __construct($id)
	{
		parent::__construct();
		assert(is_string($id) || is_numeric($id));
		$this->id = $id;
		$this->resolved = $this;
	}
	
	public function name()    { return "<proxy>"; }
	public function members() { return array(); }
	
	public function details()  { return "@".$this->id; }
	public function children() { return array(); }
	
	public function reduceToAbsolute(Scope $scope) { throw new \RuntimeException("ConcreteType_Proxy should never be asked for absolute reduction"); }
	
	public function bindProxies(array $nodes)
	{
		//\mwc\debug("type proxy {$this->id} asked to bind proxies\n");
		if (!isset($nodes[$this->id])) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Unable to resolve type proxy since no entity with id {$this->id} is known."
			);
			return;
		}
		
		$resolved = $nodes[$this->id];
		assert($resolved instanceof ConcreteType_Intf);
		
		$this->resolved = $resolved;
	}
	
	public function reduce()
	{
		//\mwc\debug("type proxy {$this->id} asked to reduce\n");
		assert($this->resolved instanceof ConcreteType);
		/*if (!$this->resolved instanceof ConcreteType_Intf) {
			throw new \RuntimeException("ConcreteType_Proxy asked to reduce without proper ConcreteType_Intf");
		}*/
		return $this->resolved;
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		return $this;
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		$ids[] = $this->id;
	}
}