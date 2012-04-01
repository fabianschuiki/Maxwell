<?php
namespace LET;

class Tuple_Impl extends Tuple
{
	public $fields;
	
	public function __construct(Scope $scope, array $fields)
	{
		parent::__construct();
		
		foreach ($fields as $name => $field) assert($field instanceof TypedNode);
		
		$this->fields = $fields;
		$this->scope  = $scope;
	}
	
	public function fields() { return $this->fields; }
}