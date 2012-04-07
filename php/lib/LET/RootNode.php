<?php
namespace LET;

class RootNode extends Node
{
	public $asns;
	public $stmts;
	
	public function __construct(Scope $scope)
	{
		$this->asns  = $nodes;
		$this->stmts = array();
		$this->scope = $scope;
	}
	
	public function children()
	{
		return array_merge($this->scope->children(), $this->stmts);
	}
	
	public function details() { return null; }
}