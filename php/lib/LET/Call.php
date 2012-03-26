<?php
namespace LET;

abstract class Call extends Expr
{
	abstract function callee();
	abstract function args();
	
	public function details()
	{
		$callee = $this->callee();
		$callee = ($callee ? $callee->details() : '?');
		
		$args = array_map(function($arg){
			return ($arg ? $arg->details() : '?');
		}, $this->args());
		$args = implode(", ", $args);
		
		return "'$callee' ($args)";
	}
	
	public function children()
	{
		return array_merge(array($this->callee()), $this->args());
	}
	
	/*public function type()
	{
		$in = array();
	}*/
}