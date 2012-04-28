<?php
namespace CET;

class TypeMember extends Node
{
	public $name;
	
	public function __construct(\LET\TypeMember_AST $node, array &$cet)
	{
		parent::__construct();
		$this->name = $node->name();
	}
	
	public function details() { return $this->name; }
}