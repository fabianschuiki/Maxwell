<?php
namespace LET;

class TypeMember_AST extends TypeMember
{
	public $asn;
	
	public function __construct(Scope $scope, \AST\VarStmt $node)
	{
		parent::__construct();
		
		$type = Type::make($scope, $node->type);
		
		$this->asn  = $node;
		$this->type = $type;
	}
	
	public function name() { return $this->asn->name->text;	}
	
	public function cloneInto(Scope $scope)
	{
		$clone = new self($scope, $this->asn);
		$clone->type = $this->type;
		return $clone;
	}
}