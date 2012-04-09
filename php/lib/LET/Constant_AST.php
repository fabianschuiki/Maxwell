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
				$types = array();
				if (strpos($this->value(), '.') === false) {
					$types[] = new TypeExpr($scope, new Ident_Impl($scope, 'int'));
				} else {
					$types[] = new TypeExpr($scope, new Ident_Impl($scope, 'float'));
				}
				$type = new TypeSet($scope, $types);
			} break;
			case 'string': {
			} break;
		}
		
		$this->asn   = $node;
		$this->type  = $type;
		$this->scope = $scope;
	}
	
	public function value()             { return $this->asn->value->text; }
	public function dataType()          { return $this->asn->value->type; }
	public function unconstrainedType() { return $this->type; }
	
	public function reduce()
	{
		if ($this->type()) $this->type = $this->type()->reduce();
		return $this;
	}
}