<?php
namespace LET;

class TypeMember extends TypedNode
{
	public $asn;
	public $type;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		$type = Type::make($scope, $node->type);
		
		$this->asn  = $node;
		$this->type = $type;
	}
	
	public function unconstrainedType() { return $this->type; }
	public function name() { return $this->asn->name->text;	}
	
	public function details()
	{
		$type = $this->type;
		$type = ($type ? $type->details() : '?');
		
		return "$type {$this->name()}";
	}
	
	public function reduce()
	{
		if ($this->type) $this->type = $this->type->reduce();
		return $this;
	}
}