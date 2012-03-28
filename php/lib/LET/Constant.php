<?php
namespace LET;

abstract class Constant extends Expr
{
	abstract function value();
	abstract function dataType();
	abstract function type();
	
	public function details()
	{
		$str = $this->value();
		if ($this->dataType() == 'string') {
			$str = "'$str'";
		}
		return $str;
	}
}