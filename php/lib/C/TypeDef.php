<?php
namespace C;

class TypeDef extends Stmt
{
	public $name;
	public $fields;
	
	public function __construct()
	{
		parent::__construct();
		$this->fields = array();
	}
	
	public function getDefinition() { return null; }
	public function getDeclaration()
	{
		$str = "typedef struct {$this->name} {\n";
		foreach ($this->fields as $field) $str .= Node::indent($field->getStmt())."\n";
		$str .= "} {$this->name};";
		return $str;
	}
	
	public function getStmt() { return $this->getDeclaration(); }
}