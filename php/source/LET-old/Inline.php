<?php
namespace LET;

class Inline extends Stmt
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\InlineStmt $node)
	{
		$this->asn   = $node;
		$this->scope = $node;
	}
}