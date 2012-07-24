<?php
namespace LET;

abstract class CallArg extends Node
{
	abstract function name();
	abstract function expr();
	
	public function details()
	{
		$expr = $this->expr();
		$name = $this->name();
		$str  = ($expr ? $expr->details() : '?');
		if ($name) {
			$str = "$name: $str";
		}
		return $str;
	}
}