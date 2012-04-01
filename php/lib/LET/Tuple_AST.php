<?php
namespace LET;

class Tuple_AST extends Tuple
{
	public $asn;
	public $fields;
	
	public function __construct(Scope $scope, \AST\TupleExpr $node)
	{
		parent::__construct();
		
		$fields = array();
		foreach ($node->exprs as $name => $field) {
			$fields[$name] = Expr::make($scope, $field);
		}
		$fields = array_filter($fields);
		
		$this->asn    = $node;
		$this->fields = $fields;
		$this->scope  = $scope;
	}
	
	public function fields() { return $this->fields; }
}