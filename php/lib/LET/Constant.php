<?php
namespace LET;

abstract class Constant extends Expr
{
	abstract function value();
	abstract function dataType();
	
	public function details()
	{
		$str = $this->value();
		if ($this->dataType() == 'string') {
			$str = "'$str'";
		}
		return $str;
	}
}