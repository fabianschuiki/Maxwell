<?php
namespace LET;

abstract class Constant extends Expr
{
	public $type;
	
	abstract function value();
	abstract function dataType();
	
	public function __construct()
	{
		parent::__construct();
		
		$type = null;
		switch ($this->dataType()) {
			case 'numeric': {
				if (strpos($this->value(), '.') === false) {
					$type = Scope::getBuiltinNode('builtin_type_int');
				} else {
					$type = Scope::getBuiltinNode('builtin_type_float');
				}
			} break;
			case 'string': {
				$type = new TypeExpr($this->scope, new Ident_Impl($this->scope, "String"));
			} break;
		}
		$this->type = $type;
	}
	
	public function details()
	{
		$str = $this->value();
		if ($this->dataType() == 'string') {
			$str = "'$str'";
		}
		return $str;
	}
	
	public function unconstrainedType() { return $this->type; }
	
	public function reduce()
	{
		if ($this->type()) $this->type = $this->type()->reduce();
		return $this;
	}
	
	public function reduceToAbsolute(Scope $scope)
	{
		echo "unbinding constant {$this->desc()}\n";
		return new Constant_Impl($scope, $this->value(), $this->dataType());
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		$this->type = $this->type->unbindFromInterfaces($root);
		return $this;
	}
}