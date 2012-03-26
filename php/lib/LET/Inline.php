<?php
namespace LET;

class Inline extends Node
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\InlineStmt $node)
	{
		$this->asn   = $node;
		$this->scope = $node;
	}
}