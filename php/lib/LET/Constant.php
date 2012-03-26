<?php
namespace LET;

abstract class Constant extends Expr
{
	abstract function value();
	abstract function type();
	
	public function details()
	{
		$str = $this->value();
		if ($this->type() == 'string') {
			$str = "'$str'";
		}
		return $str;
	}
}