<?php
namespace AST;

class NativeTypeExpr extends Expr
{
	public $name;
	public $range;
	
	public function __construct(array $tokens)
	{
		$this->name = implode(' ', array_map(function($t){ return $t->text; }, $tokens));
		$this->range = \Range::union(array_map(function($t){ return $t->range; }, $tokens));
	}
	
	public function nice() { return "Native Type"; }
}