<?php
namespace LET;

class Scope
{
	public $node;
	public $outer;
	
	public $types = array();
	public $funcs = array();
	public $vars  = array();
	
	public function __construct($outer = null, $node = null)
	{
		assert(!$outer || $outer instanceof Scope);
		assert(!$node  || $node  instanceof Node);
		$this->outer = $outer;
		$this->node  = $node;
	}
	
	public function add($node)
	{
		if (!$node) return;
		assert($node instanceof Node);
		$node->scope = $this;
		
		//Add to node to the appropriate container.
		if ($node instanceof ConcreteType) $this->types[] = $node; else
		if ($node instanceof Func)         $this->funcs[] = $node; else
		if ($node instanceof FuncArg || $node instanceof Variable) {
			$existing = null;
			foreach ($this->vars as $variable) {
				if ($variable->name() == $node->name()) {
					$existing = $variable;
					break;
				}
			}
			if (!$existing) {
				$this->vars[] = $node;
			} else {
				global $issues;
				$issues[] = new \Issue(
					'error',
					"An entity named '{$node->name()}' already exists.",
					$node,
					$existing
				);
			}
		} else {
			trigger_error($node->kind()." not allowed in scope.");
		}
	}
	
	public function children()
	{
		return array_merge($this->types, $this->funcs);
	}
	
	public function __call($name, array $args)
	{
		if ($this->node) call_user_func_array(array($this->node, $name), $args);
		foreach ($this->children() as $node) {
			call_user_func_array(array($node, $name), $args);
			if ($node->subscope) call_user_func_array(array($node->subscope, $name), $args);
		}
	}
	
	///Searches the scope hierarchy (this and its parents) for nodes with the given name.
	public function find($name, $noVars = false, $noBuiltin = false)
	{
		if (!$name) return array();
		assert(is_string($name));
		
		$filter = function($node) use ($name) { return ($node->name() == $name); };
		
		$vars = array();
		if (!$noVars) {
			$vars = array_filter($this->vars, $filter);
			//The following is commented out as it does break type inference for now. x does not introduce a type constraint on the type's member, whereas this.x does.
			/*if ($this->node instanceof Func) {
				$inputs = $this->node->inputs();
				if (count($inputs) > 0 && $inputs[0]->name() == "this" && $inputs[0]->type() instanceof ConcreteType) {
					foreach ($inputs[0]->type()->members() as $member) {
						if ($member->name() == $name) $vars[] = $member;
					}
				}
			}*/
		}
		
		$outer = array();
		if ($this->outer) {
			$outer = $this->outer->find($name, $noVars || count($vars));
		} else if (static::$builtin !== $this && !$noBuiltin) {
			if (!static::$builtin) static::makeBuiltin();
			$outer = static::$builtin->find($name, true);
		}
		
		$imported = array();
		//if ($this->node) echo "  - node is ".get_class($this->node)."\n";
		if ($this->node instanceof Root && is_array($this->node->importedRoots)) {
			//echo "  - consulting imported roots\n";
			foreach ($this->node->importedRoots as $root) {
				$imported = array_merge($imported, $root->scope->find($name, true, true));
			}
			/*if ($imported) {
				\mwc\debug(count($imported)." imported nodes named '$name' found\n");
				foreach ($imported as $imp) {
					\mwc\debug("- ".$imp->desc()."\n");
				}
			}*/
		}
		
		$nodes = array_merge(
			array_filter($this->types, $filter),
			array_filter($this->funcs, $filter),
			$vars,
			$outer,
			$imported
		);
		
		return $nodes;
	}
	
	public function stripGenerics()
	{
		$specificFilter = function($node) { return $node->isSpecific(); };
		$this->types = array_filter($this->types, $specificFilter);
		$this->funcs = array_filter($this->funcs, $specificFilter);
		
		foreach ($this->children() as $child) $child->subscope->stripGenerics();
	}
	
	public function reduceToInterface($scope = null)
	{
		assert(!$scope || $scope instanceof Scope);
		
		$s = new self;
		$s->outer = $scope;
		$s->node  = $this->node;
		
		foreach ($this->funcs as $func) $s->funcs[] = $func->reduceToInterface($s);
		foreach ($this->types as $type) $s->types[] = $type->reduceToInterface($s);
		
		return $s;
	}
	
	public function rootNode()
	{
		for ($root = $this; $root && !$root->node instanceof Root; $root = $root->outer);
		return ($root ? $root->node : null);
	}
	
	static private $builtin = null;
	static private $builtinMap = null;
	static private function makeBuiltin()
	{
		$scope = new Scope;
		
		$primitives    = array('int', 'float');
		$operators     = array('+', '-', '*', '/', '=');
		$boolOperators = array('>', '<', '==', '!=', '<=', '>=');
		
		$bool = new PrimitiveBuiltinType($scope, 'bool');
		foreach ($boolOperators as $operator) new BuiltinBinaryOp($scope, $operator, $bool, $bool);

		foreach ($primitives as $primitive) {
			$type = new PrimitiveBuiltinType($scope, $primitive);
			foreach ($operators     as $operator) new BuiltinBinaryOp($scope, $operator, $type);
			foreach ($boolOperators as $operator) new BuiltinBinaryOp($scope, $operator, $type, $bool);
		}
		
		new BuiltinUnaryOp($scope, 'new', new GenericType);
		
		$map = array();
		foreach ($scope->types as $type) $map[$type->id] = $type;
		foreach ($scope->funcs as $func) $map[$func->id] = $func;
		
		static::$builtin = $scope;
		static::$builtinMap = $map;
	}
	
	static public function getBuiltinNodes()
	{
		if (!static::$builtinMap) static::makeBuiltin();
		return static::$builtinMap;
	}
	
	static public function getBuiltinNode($id)
	{
		if (!static::$builtinMap) static::makeBuiltin();
		if (isset(static::$builtinMap[$id])) return static::$builtinMap[$id];
		return null;
	}
}