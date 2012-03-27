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
	
	/*public function type()
	{
		switch ($this->dataType()) {
			//TODO: use the actual built-in types here.
			case 'numeric': return new TypeExpr($this->scope, new Ident_Impl($this->scope, 'int')); break;
		}
		return null;
	}*/
}