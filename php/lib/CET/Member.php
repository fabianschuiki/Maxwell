<?php
namespace CET;

class Member extends Node
{
	public $node;
	public $member;
	public $pointer;
	
	public function __construct(\LET\Member $node, array &$cet)
	{
		$typeMember = $node->typeMember();
		assert($typeMember);
		
		$memberID = $typeMember->id;
		if (!isset($cet[$memberID])) \mwc\Compiler::error("no CET node $id found for member {$typeMember->desc()}");
		$this->member = $cet[$memberID];
		
		$this->node = Node::make($node->expr(), $cet);
	}
	
	public function isPointer() { return $this->member->isPointer(); }
	public function details() { return "{$this->member->name()}"; }
	
	public function generateCode(\C\Container $root)
	{
		$expr  = $this->node->generateCode($root)->getExpr();
		$expr .= ($this->node->isPointer() ? "->" : ".");
		$expr .= $this->member->name();
		
		return new \C\Expr($expr);
	}
}