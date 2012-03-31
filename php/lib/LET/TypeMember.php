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
	
	public function children()
	{
		$type = $this->type;
		if (!$type || $type instanceof ConcreteType) return array();
		return array($type);
	}
	
	public function reduce()
	{
		if ($this->type) {
			echo "reducing {$this->desc()} with type being of class ".get_class($this->type)."\n";
			$this->type = $this->type->reduce();
		}
		return $this;
	}
}