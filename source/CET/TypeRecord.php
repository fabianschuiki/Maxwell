<?php
namespace CET;

class TypeRecord extends Node
{
	public $type;
	
	public function __construct(Type $type)
	{
		$this->type = $type;
	}
	
	public function details() { return "{$this->type->name()}"; }
	
	public function getType() { return "Type_t"; }
	
	public function generateCode(\C\Container $root)
	{
		$fields = array();
		$fields[] = "\"{$this->type->name}\"";
		$fields[] = "sizeof({$this->type->name()})";
		
		$value = "({$this->getType()}) {\n\t".implode(",\n\t", $fields)."\n}";
		
		$node = new \C\GlobalVar;
		$node->signature = "const {$this->getType()} {$this->type->recordName()}";
		$node->value = $value;
		$root->add($node);
	}
}