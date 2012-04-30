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
	
	public function name()    { return "<type proxy>"; }
	public function members() { return array(); }
	
	public function details()  { return "@".$this->id; }
	public function children() { return array(); }
	
	public function isSpecific() { return false; }
	
	public function reduceToAbsolute(Scope $scope) { /*throw new \RuntimeException("ConcreteType_Proxy should never be asked for absolute reduction");*/return $this; }
	
	public function bindProxies(array $nodes)
	{
		$builtin = Scope::getBuiltinNode($this->id);
		if ($builtin) {
			$this->resolved = $builtin;
			return;
		}
		
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
		assert($resolved instanceof ConcreteType);
		
		$this->resolved = $resolved;
	}
	
	public function reduce()
	{
		assert($this->resolved instanceof Type);
		return $this->resolved;
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		return new self($this->id);
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		$ids[] = $this->id;
	}
}