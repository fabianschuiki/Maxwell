<?php
namespace LET;

class Func_Intf extends Func
{
	public $name;
	public $inputs;
	public $outputs;
	public $subscope;
	
	public function __construct(Scope $scope, Func $func)
	{
		parent::__construct();
		
		$subscope = $func->subscope->reduceToInterface($scope);
		$subscope->node = $this;
		
		$inputs  = array();
		$outputs = array();
		foreach ($func->inputs() as $i) {
			$a = $i->reduceToInterface($subscope);
			$a->parent = $this;
			$inputs[] = $a;
		}
		foreach ($func->outputs() as $o) {
			$a = $o->reduceToInterface($subscope);
			$a->parent = $this;
			$outputs[] = $a;
		}
		
		$this->id       = $func->id;
		$this->name     = strval($func->name());
		$this->inputs   = $inputs;
		$this->outputs  = $outputs;
		$this->subscope = $subscope;
		$this->scope    = $scope;
	}
	
	public function name()     { return $this->name; }
	public function inputs()   { return $this->inputs; }
	public function outputs()  { return $this->outputs; }
	public function subscope() { return $this->subscope; }
	public function stmts()    { return array(); }
	
	public function specialize(FuncType $type, array &$specializations)
	{
		$root = $this->scope->rootNode();
		assert($root instanceof Root);
		
		foreach (array($type->in(), $type->out()) as $tuple) {
			foreach ($tuple->fields as $name => $arg) {
				if (!$arg instanceof MemberConstrainedType || !$arg->type instanceof ConcreteType) continue;
				$tuple->fields[$name] = $arg->type->specialize($arg, $specializations);
			}
		}
		
		$reduced = $type->reduceToAbsolute(new Scope);
		$reduced->originalID = $this->id;
		foreach ($root->specializations as $id => $spec) {
			//if (Type::equalTwo($spec, $reduced)) return $type;
			if ($spec->originalID === $this->id) return new Func_Proxy($id);
		}
		
		$id = trim(`uuidgen`);
		$root->specializations[$id] = $reduced;
		return /*$type*/new Func_Proxy($id);
	}
	
	public function reduceToInterface() { throw new \RuntimeExcpetion("Func_Intf should never be asked for reduction"); }
	
	public function registerExternal(Root $root)
	{
		$root->externalNodes[] = $this->id;
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		$ids[] = $this->id;
	}
}