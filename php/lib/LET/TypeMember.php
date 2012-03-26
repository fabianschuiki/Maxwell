<?php
namespace LET;

class TypeMember extends Node
{
	public $asn;
	
	public function __construct(\AST\VarStmt $node)
	{
		$this->asn = $node;
	}
	
	public function name()
	{
		return $this->asn->name->text;
	}
	
	public function type()
	{
		return $this->asn->type->name->text;
	}
	
	public function details()
	{
		return "{$this->type()} {$this->name()}";
	}
}