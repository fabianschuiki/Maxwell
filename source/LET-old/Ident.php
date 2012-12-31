<?php
namespace LET;

abstract class Ident extends Expr
{
	public $boundTo;
	public $boundNodes;
	public $boundNodesCommonType;
	public $lastConfirmedTypeConstraint;
	
	abstract function name();
	
	public function details()  { return $this->name(); }
	public function children() { return array(); }
	
	public function bind($weak = false)
	{
		\Analyzer::$stat_bind++;
		if (Type::equalTwo($this->lastConfirmedTypeConstraint, $this->typeConstraint))
			\Analyzer::$stat_bindInVain++;
		$this->lastConfirmedTypeConstraint = $this->typeConstraint;
		
		//\mwc\debug("- binding {$this->name()}\n");
		global $issues;
		$nodes = $this->scope->find($this->name());
		$unfiltered = $nodes;
		if (count($unfiltered) == 0 && !$weak) {
			$issues[] = new \Issue(
				'error',
				"Entity '{$this->name()}' is unknown.",
				$this
			);
		}
		
		$type = $this->typeConstraint;
		$tc = '?';
		//foreach ($nodes as $node) \mwc\debug("  - found {$node->desc()}\n");
		if ($type) {
			//\mwc\debug("  - with {$type->desc()}\n");
			$nodes = array_filter($nodes, function($node) use ($type) { return $node->type() && (Type::intersect($node->type(), $type) != null); });
			//\mwc\debug("  - ".count($unfiltered)." found, ".count($nodes)." filtered\n");
			$tc = $type->details();
		}
		//foreach ($nodes as $node) \mwc\debug("  - keeping {$node->desc()}\n");
		
		//Fill in tuple operation placeholders.
		/*if ($type instanceof FuncType) {
			$ins = $type->in()->fields;
			if (count($ins) == 2 && $ins[0] instanceof TypeTuple && $ins[1] instanceof TypeTuple) {
				\mwc\debug("chance to fill in implicit tuple operation with type {$type->in()->details()}\n");
				//For now, the LHS of the operator decides what type the RHS and result will be. This might need to change in the future to make the language actually useful.
				$nodes[] = new TupleBinaryOp($this->name(), $ins[0]);
			}
		}*/
		
		//TODO: we need some mature selection scheme for selecting the best node. Maybe some sort of score?
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
		usort($nodes, function($a,$b){ return 0; });
		//echo "binding identifier {$this->name()} -> ".count($unfiltered)." nodes, ".count($nodes)." ".($anySpecific ? 'specific' : '')." nodes match type $tc.\n";
		
		$boundTo = $this->boundTo; //WARNING: this might be an ugly hack. Haven't considered all implications. Should prevent bound identifiers from losing their binding.
		if (count($nodes) == 0 && count($unfiltered) > 0) {
			$cands = implode("\n", array_map(function($c){ return $c->details(); }, $unfiltered));
			$issues[] = new \Issue(
				'error',
				"No entity named '{$this->name()}' is of type '{$type->details()}'. Candidates are:\n$cands",
				$this,
				$unfiltered
			);
		}
		if (count($nodes) == 0) $boundTo = null;
		if (count($nodes) == 1) $boundTo = $nodes[0];
		if (count($nodes)) {
			$in  = new GenericType;
			$out = new GenericType;
			//\mwc\debug("finding common node type for {$this->name()}\n");
			foreach ($nodes as $node) {
				if (!$node instanceof TypedNode) continue;
				$nodeType = $node->type();
				if (!$nodeType instanceof FuncType) continue;
				//\mwc\debug("- {$node->type()->desc()}\n");
				
				if ($in  && $nodeType->in())  $in  = Type::intersectTwo($in,  $nodeType->in());
				if ($out && $nodeType->out()) $out = Type::intersectTwo($out, $nodeType->out());
			}
			if (!$in)  $in  = new GenericType;
			if (!$out) $out = new GenericType;
			if ($in instanceof GenericType && $out instanceof GenericType) {
				$this->boundNodesCommonType = new GenericType;
			} else {
				$this->boundNodesCommonType = new FuncType($this->scope, $in, $out);
			}
			//TODO: actually make the above code work. Maybe through option types / type sets.
			$this->boundNodesCommonType = new GenericType;
		} else {
			$this->boundNodesCommonType = null;
		}
		
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
		/*if ($this->boundTo instanceof Func) {
			return $this->boundTo->type();
		}*/
		/*if (is_array($this->boundNodes)) {
			return new GenericType;
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
		}
		return null;*/
		return $this->boundNodesCommonType;
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
		if (count($this->boundNodes) > 1 && !$this->boundTo) {
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
			$this->boundNodes = array($spec);
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
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new Ident_Impl($scope, $this->name());
	}
	
	public function unbindFromInterfaces(Root $root)
	{
		//\mwc\debug("unbindFromInterfaces ident {$this->name()}, ".count($this->boundNodes)." nodes\n");
		/*$this->lastConfirmedTypeConstraint = new GenericType;
		if ($this->boundTo) $this->boundTo = $this->boundTo->unbindFromInterfaces();
		if ($this->boundNodes) $this->boundNodes = array_map(function($n){ return $n->unbindFromInterfaces(); }, $this->boundNodes);
		$this->boundNodesCommonType = null;*/
		/*if ($this->boundTo) $this->boundTo = $this->boundTo->unbindFromInterfaces($root);
		if ($this->boundNodes) foreach ($this->boundNodes as $bn) $root->externalNodes[] = $bn->id;*/
		//if ($this->boundTo) $this->boundTo->registerExternal($root);
		//if ($this->boundNodes) foreach ($this->boundNodes as $bn) $bn->registerExternal($root);
		//if ($this->boundNodes) $this->boundNodes = array_map(function($n) use ($root) { return $n->unbindFromInterfaces($root); }, $this->boundNodes);
		
		if ($this->boundTo) $this->boundTo = $this->boundTo->unbindFromInterfaces($root);
		//if ($this->boundNodes) $this->boundNodes = array_map(function($m) use ($root) { return $m->unbindFromInterfaces($root); }, $this->boundNodes);
		
		//$this->boundTo = null;
		$this->boundNodes = null;
		$this->boundNodesCommonType = null;
		$this->lastConfirmedTypeConstraint = null;
		return parent::unbindFromInterfaces($root);
	}
	
	/*public function bindProxies(array $nodes)
	{
		if ($this->boundTo instanceof ConcreteType_Proxy || $this->boundTo instanceof Func_Proxy) {
			echo "bind proxies {$this->boundTo->id}\n";
			print_r(array_keys($nodes));
			$this->boundTo->bindProxies($nodes);
			$this->boundTo = $this->boundTo->reduce();
			$this->boundNodes = array($this->boundTo);
			$this->boundNodesCommonType = new GenericType;
			echo " -> bound to {$this->boundTo->desc()}\n";
		}
	}*/
	
	/*public function gatherExternalNodeIDs(array &$ids)
	{
		echo "gathering for ident {$this->name()}\n";
		if ($this->boundTo) $this->boundTo->gatherExternalNodeIDs($ids);
		if ($this->boundNodes) foreach ($this->boundNodes as $bn) $bn->gatherExternalNodeIDs($ids);
	}*/
}