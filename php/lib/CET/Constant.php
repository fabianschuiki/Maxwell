<?php
namespace CET;

class Constant extends Node
{
	public $value;
	
	public function __construct(\LET\Constant $node, array &$cet)
	{
		$this->value = $node->value();
	}
	
	public function details() { return ""; }
	
	public function generateCode(\C\Container $root)
	{
		return new \C\Expr("{$this->value}");
	}
}