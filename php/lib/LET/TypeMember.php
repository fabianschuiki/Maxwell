<?php
namespace LET;

class TypeMember extends Node
{
	public $asn;
	public $type;
	
	public function __construct(\AST\VarStmt $node)
	{
		$this->asn  = $node;
		$this->type = new InferredType\Named($node->type->name->text);
	}
	
	public function type() { return $this->type; }
	public function name() { return $this->asn->name->text;	}
	
	public function details()
	{
		return "{$this->type()->details()} {$this->name()}";
	}
}