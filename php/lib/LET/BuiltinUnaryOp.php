<?php
namespace LET;

class BuiltinUnaryOp extends Func
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
		$this->id = "builtin_unop_{$name}_{$type->name()}_{$ret}";
		
		if (!$returnType) $returnType = $type;
		assert($returnType instanceof Type);
		
		$args     = array();
		$subscope = new Scope($scope, $this);
		
		$in  = new FuncArg_Impl($subscope, $type, 'a');
		$in ->parent = $this;
		$out = new FuncArg_Impl($subscope, $returnType, 'r');
		$out->parent = $this;
		
		$this->name     = $name;
		$this->inputs   = array($in);
		$this->outputs  = array($out);
		$this->scope    = $scope;
		$this->subscope = $subscope;
		
		$scope->add($this);
	}
	
	public function name()     { return $this->name; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function stmts()    { return array(); }
	public function subscope() { return $this->subscope; }
	
	public function nice() { return "Builtin Unary Operator {$this->name}"; }
	
	public function gatherExternalNodeIDs(array &$ids)
	{
	}
	
	public function specialize()
	{
		return $this;
	}
}