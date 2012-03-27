<?php
namespace LET;

class Constant_AST extends Constant
{
	public $asn;
	public $type;
	
	public function __construct(Scope $scope, \AST\ConstExpr $node)
	{
		$type = null;
		switch ($node->value->type) {
			case 'numeric': {
				$type = new TypeExpr($scope, new Ident_Impl($scope, 'int'));
			} break;
			case 'string': {
			} break;
		}
		
		$this->asn   = $node;
		$this->type  = $type;
		$this->scope = $scope;
	}
	
	public function value()    { return $this->asn->value->text; }
	public function dataType() { return $this->asn->value->type; }
	public function type()     { return $this->type; }
	
	public function reduce()
	{
		if ($this->type) $this->type = $this->type->reduce();
		return $this;
	}
}