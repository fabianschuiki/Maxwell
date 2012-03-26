<?php
namespace LET;

abstract class Constant extends Expr
{
	abstract function value();
	abstract function dataType();
	
	public function details()
	{
		$str = $this->value();
		if ($this->type() == 'string') {
			$str = "'$str'";
		}
		return $str;
	}
	
	public function type()
	{
		switch ($this->dataType()) {
			case 'numeric': return new InferredType\Named('int'); break;
		}
		return null;
	}
}