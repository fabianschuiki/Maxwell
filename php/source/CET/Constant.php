<?php
namespace CET;

class Constant extends Node
{
	public $value;
	public $type;
	public $name;
	
	public function __construct(\LET\Constant $node, array &$cet)
	{
		$this->value = $node->value();
		$this->type  = $node->dataType();
		$this->name  = uniqid("const_");
	}
	
	public function details() { return ""; }
	
	public function generateCode(\C\Container $root)
	{
		if ($this->type == 'numeric') return new \C\Expr("{$this->value}");
		if ($this->type == 'string') {
			//Create the data object for the string data.
			$fields = array();
			$fields[] = "&Data_type";
			$fields[] = "\"{$this->value}\"";
			$fields[] = strlen($this->value);
			
			$dataName = "{$this->name}_data";
			$data = new \C\GlobalVar;
			$data->signature = "const static Data_t $dataName";
			$data->value = "{\n\t".implode(",\n\t", $fields)."\n}";
			$root->add($data);
			
			//Create the string object which contains the data.
			$fields = array();
			$fields[] = "&String_type";
			$fields[] = "&$dataName";
			
			$str = new \C\GlobalVar;
			$str->signature = "const static String_t {$this->name}";
			$str->value = "{\n\t".implode(",\n\t", $fields)."\n}";
			$root->add($str);
			
			return new \C\Expr($this->name);
		}
		
		\mwc\Compiler::error("'{$this->type}' constants not supported");
	}
}