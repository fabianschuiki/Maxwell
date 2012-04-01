<?php
namespace LET;

abstract class Ident extends Expr
{
	public $boundTo;
	public $boundNodes;
	//public $lastConfirmedType;
	
	abstract function name();
	
	public function details()  { return $this->name(); }
	public function children() { return array(); }
	
	public function bind()
	{
		global $issues;
		$nodes = $this->scope->find($this->name());
		$unfiltered = $nodes;
		if (count($unfiltered) == 0) {
			$issues[] = new \Issue(
				'error',
				"Entity '{$this->name()}' is unknown.",
				$this
			);
		}
		
		$type = $this->typeConstraint;
		$tc = '?';
		if ($type) {
			$nodes = array_filter($nodes, function($node) use ($type) { return $node->type() && (Type::intersect($node->type(), $type) != null); });
			$tc = $type->details();
		}
		if ($type->isSpecific()) {
			$anySpecific = false;
			foreach ($nodes as $node) {
				if ($node->isSpecific()) {
					$anySpecific = true;
					break;
				}
			}
			if ($anySpecific) $nodes = array_filter($nodes, function($node) { return $node->isSpecific(); });
		}
		sort($nodes);
		//echo "binding identifier {$this->name()} -> ".count($unfiltered)." nodes, ".count($nodes)." ".($anySpecific ? 'specific' : '')." nodes match type $tc.\n";
		
		$boundTo = $this->boundTo; //WARNING: this might be an ugly hack. Haven't considered all implications. Should prevent bound identifiers from losing their binding.
		if (count($nodes) == 0 && count($unfiltered) > 0) {
			$issues[] = new \Issue(
				'error',
				"No entity named '{$this->name()}' is of type '{$type->details()}'. Candidates are:",
				$this,
				$unfiltered
			);
		}
		if (count($nodes) == 0) $boundTo = null;
		if (count($nodes) == 1) $boundTo = $nodes[0];
		
		$this->boundTo    = $boundTo;
		$this->boundNodes = $nodes;
		$this->maybeTypeChanged();
	}
	
	public function unconstrainedType()
	{
		if ($this->boundTo instanceof Type) {
			return $this->boundTo;
		}
		if ($this->boundTo instanceof TypedNode) {
			return $this->boundTo->type();
		}
		if (is_array($this->boundNodes)) {
			$in  = new GenericType;
			$out = new GenericType;
			foreach ($this->boundNodes as $node) {
				if (!$node instanceof TypedNode) continue;
				$nodeType = $node->type();
				if (!$nodeType instanceof FuncType) continue;
				
				if ($in  && $nodeType->in())  $in  = Type::intersectTwo($in,  $nodeType->in());
				if ($out && $nodeType->out()) $out = Type::intersectTwo($out, $nodeType->out());
			}
			if (!$in)  $in  = new GenericType;
			if (!$out) $out = new GenericType;
			if ($in instanceof GenericType && $out instanceof GenericType) return new GenericType;
			return new FuncType($this->scope, $in, $out);
			/*$type = new GenericType;
			foreach ($this->boundNodes as $node) {
				if (!$node instanceof TypedNode || $node instanceof Type) continue;
				$other = $node->type();
				if (!$other) continue;
				echo "intersecting with {$other->details()}\n";
				
				if ($type instanceof FuncType && $other instanceof FuncType) {
					$in  = Type::intersect($type->in(),  $other->in(),  $this->scope);
					$out = Type::intersect($type->out(), $other->out(), $this->scope);
					if (!$in)  $in  = new GenericType;
					if (!$out) $out = new GenericType;
					echo "  got {$in->details()} -> {$out->details()}\n";
					$type = new FuncType($this->scope, $in, $out);
				} else {
					$type = Type::intersect($type, $node->type(), $this->scope);
				}
			}
			return $type;*/
		}
		return null;
	}
	
	public function spawnConstraints(array &$constraints)
	{
		parent::spawnConstraints($constraints);
		if ($this->boundTo instanceof Variable || $this->boundTo instanceof FuncArg) {
			$constraints[] = new EqualTypeConstraint($this, $this->boundTo);
		}
	}
	
	//Not sure whether this is required. The identifier needs to refilter the list of nodes when its type constraint changes. If only for funcs, this can be done in Call.
	/*public function imposeTypeConstraint(Type $type)
	{
		//$typeBefore = $this->type();
		parent::imposeTypeConstraint($type);
		$type = $this->type();
		if ($type != $this->lastConfirmedType && $this->lastConfirmedType) {
			$this->lastConfirmedType = $type;
			if ($this->parent) $this->parent->notifyNodeChangedType($this);
			$this->propagateTypeChange();
		}
		$this->lastConfirmedType = $type;
	}*/
	
	/*public function constraintTarget() { return ($this->boundTo && $this->boundTo instanceof Variable ? $this->boundTo : null); }*/
	public function complainAboutAmbiguities()
	{
		parent::complainAboutAmbiguities();
		if (count($this->boundNodes) > 1) {
			global $issues;
			$issues[] = new \Issue(
				'error',
				"Entity '{$this->name()}' is ambiguous. It may refer to:",
				null,
				$this->boundNodes
			);
		}
	}
	
	public function buildSpecializations(array &$specializations)
	{
		parent::buildSpecializations($specializations);
		
		if (($this->boundTo instanceof Func /*|| $this->boundTo instanceof ConcreteType*/) && !$this->boundTo->isSpecific()) {
			$spec = $this->boundTo->specialize($this->type(), $specializations);
			/*echo "asked to specialize {$this->boundTo->details()} for {$this->type()->details()}\n";
			echo "  got {$spec->details()}\n";*/
			$this->boundTo = $spec;
		}
	}
	
	public function notifyNodeChangedType(Node $node)
	{
		if ($this->boundTo === $node) {
			/*echo "        binding is affected: '{$this->boundTo->details()}'\n";
			echo "        lastConfirmedType:   '{$this->lastConfirmedType->details()}'\n";
			echo "        type:                '{$this->type()->details()}'\n";*/
			$this->maybeTypeChanged();
		}
		parent::notifyNodeChangedType($node);
	}
}