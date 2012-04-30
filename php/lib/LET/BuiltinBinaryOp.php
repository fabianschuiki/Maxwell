<?php
namespace LET;

class BuiltinBinaryOp extends Func
{
	public $name;
	public $inputs;
	public $outputs;
	public $subscope;
	
	public function __construct(Scope $scope, $name, Type $type, $returnType = null)
	{
		parent::__construct();
		assert(is_string($name));
		
		$ret = ($returnType ? $returnType->name() : $type->name());
		$this->id = "builtin_binop_{$name}_{$type->name()}_{$ret}";
		
		if (!$returnType) $returnType = $type;
		assert($returnType instanceof Type);
		
		$args     = array();
		$subscope = new Scope($scope, $this);
		
		foreach (array('a' => $type, 'b' => $type, 'r' => $returnType) as $argname => $argtype) {
			$arg = new FuncArg_Impl($subscope, $argtype, $argname);
			$arg->parent = $this;
			$args[] = $arg;
		}
		$outputs = array(array_pop($args));
		$inputs  = $args;
		
		$this->name     = $name;
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		$this->scope    = $scope;
		$this->subscope = $subscope;
		
		$scope->add($this);
	}
	
	public function name()     { return $this->name; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function stmts()    { return array(); }
	public function subscope() { return $this->subscope; }
	
	public function nice() { return "Builtin Operator {$this->name}"; }
	
	public function gatherExternalNodeIDs(array &$ids)
	{
	}
}