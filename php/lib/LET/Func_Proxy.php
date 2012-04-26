<?php
namespace LET;

class Func_Proxy extends Func
{
	public $resolved;
	
	public function __construct($id)
	{
		parent::__construct();
		assert(is_string($id) || is_numeric($id));
		$this->id = $id;
	}
	
	public function name() { return "<proxy>"; }
	public function inputs() { return array(); }
	public function outputs() { return array(); }
	public function stmts() { return array(); }
	public function subscope() { return null; }
	
	public function details() { return "@".$this->id; }
	
	public function reduceToAbsolute(Scope $scope) { throw new \RuntimeException("Func_Proxy should never be asked for absolute reduction"); }
	
	public function bindProxies(array $nodes)
	{
		if (!isset($nodes[$this->id])) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Unable to resolve function proxy since no entity with id {$this->id} is known."
			);
			return;
		}
		
		$resolved = $nodes[$this->id];
		assert($resolved instanceof Func_Intf);
		
		$this->resolved = $resolved;
	}
	
	public function reduce()
	{
		assert($this->resolved instanceof Func);
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