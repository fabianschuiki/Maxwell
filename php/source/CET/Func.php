<?php
namespace CET;

class Func extends Node
{
	public $name;
	public $ins;
	public $outs;
	public $stmts;
	
	private $returnVarName;
	
	public function __construct(\LET\Func $node, array &$cet)
	{
		parent::__construct();
		
		$map  = function($a) use (&$cet) { return $cet[$a->id] = Node::make($a, $cet); };
		$ins  = array_map($map, $node->inputs());
		$outs = array_map($map, $node->outputs());
		
		$this->name  = strval($node->name());
		$this->ins   = $ins;
		$this->outs  = $outs;
		$this->stmts = array();
	}
	
	public function name() { return $this->name; }
	
	public function details() { return "{$this->name()}"; }
	
	public function process(\LET\Func $node, array &$cet)
	{
		foreach ($node->inputs()  as $in)  { $a = $cet[$in ->id]; $a->process($in,  $cet); $a->func = $this; }
		foreach ($node->outputs() as $out) { $a = $cet[$out->id]; $a->process($out, $cet); $a->func = $this; }
		
		foreach ($node->stmts() as $stmt) {
			$s = Node::make($stmt, $cet);
			$this->stmts[] = $s;
			$cet[$stmt->id] = $s;
		}
		
		if (count($this->outs) == 1) {
			$this->returnVarName = $this->outs[0]->name();
		} else {
			$this->returnVarName = "ret";
		}
	}
	
	public function getReturnType()
	{
		if (count($this->outs) == 0) return 'void';
		if (count($this->outs) == 1) return $this->outs[0]->getType();
		return "{$this->name()}_ret";
	}
	
	public function generateCode(\C\Container $root)
	{
		//If the function has multiple return arguments, create the structure to hold the result.
		if (count($this->outs) > 1) {
			$ret = new \C\TypeDef;
			$ret->name = $this->getReturnType();
			foreach ($this->outs as $out) $ret->fields[] = new \C\Stmt($out->getDefinition());
			$root->add($ret);
		}
		
		$args = array_map(function($i) { return $i->getDefinition(); }, $this->ins);
		
		$node = new \C\Func;
		$node->signature = "{$this->getReturnType()} {$this->name()}(".implode(", ", $args).")";
		
		if (count($this->outs) > 0) $node->body->add(new \C\Stmt("{$this->getReturnType()} {$this->returnVarName}"));
		
		foreach ($this->stmts as $stmt) {
			$s = $stmt->generateCode($node->body);
			if ($s)	$node->body->add($s);
		}
		
		if (count($this->outs) > 0) $node->body->add(new \C\Stmt("return {$this->returnVarName}"));
		
		$root->add($node);
		return null;
	}
	
	/// Returns a C expr for using the given argument inside the function body.
	public function getArgReference(FuncArg $arg)
	{
		if (in_array($arg, $this->ins, true)) return new \C\Expr($arg->name());
		if (in_array($arg, $this->outs, true)) {
			$expr = $this->returnVarName;
			if (count($this->outs) > 1) $expr .= ".{$arg->name()}";
			return new \C\Expr($expr);
		}
		
		throw new \RuntimeException("FuncArg {$arg->desc()} is not part of {$this->desc()}.");
	}
}