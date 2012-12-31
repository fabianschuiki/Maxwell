<?php
namespace LET;

abstract class Call extends Expr
{
	public $typeProxy;
	
	abstract function callee();
	abstract function args();
	
	public function details()
	{
		$callee = $this->callee();
		$callee = ($callee ? $callee->details() : '?');
		
		$args = $this->args();
		$args = ($args ? $args->details() : '?');
		
		return "'$callee' $args";
	}
	
	public function children()
	{
		$children = array($this->callee(), $this->args());
		if ($this->typeProxy) $children[] = $this->typeProxy;
		return $children;
	}
	
	public function nice()
	{
		$callee = $this->callee();
		if ($callee instanceof Ident) return "Call to '{$callee->name()}'";
		return parent::nice();
	}
	
	public function unconstrainedType()
	{
		$callee = $this->callee();
		if ($callee) {
			$func = $callee->type();
			if ($func instanceof FuncType) {
				$out = $func->out();
				if ($out instanceof TypeTuple) {
					$fields = $out->fields;
					if (count($fields) == 1) return array_pop($fields);
				}
				return $out;
			}
		}
		return null;
	}
	
	/// Returns the FuncType requried by this call. It is dictated by the arguments' types and the call's type constraint.
	private function funcType()
	{
		$args = $this->args()->type();
		if (!$args) $args = new GenericType;
		return new FuncType($this->scope, $args, $this->typeConstraint);
	}
	
	private function imposeFuncTypeOnCallee()
	{
		$callee = $this->callee();
		if ($callee) {
			$callee->imposeTypeConstraint($this->funcType());
			$callee->bind();
			$callee->reduce();
		}
	}
	
	public function spawnConstraints(array &$constraints)
	{
		if (!$this->typeProxy) $this->typeProxy = new CallTypeProxy($this);
		parent::spawnConstraints($constraints);
	}
	
	public function clearConstraints()
	{
		parent::clearConstraints();
		$this->imposeFuncTypeOnCallee();
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		parent::imposeTypeConstraint($type);
		$this->imposeFuncTypeOnCallee();
	}
	
	public function notifyNodeChangedType(Node $node)
	{
		if ($node === $this->args()) {
			//echo "\033[32mnotify\033[0m: {$this->desc()} \033[1margument\033[0m type changed\n";
			$this->imposeFuncTypeOnCallee();
		}
		if ($node === $this->typeProxy) {
			//echo "\033[32mnotify\033[0m: {$this->desc()} \033[1mreturn\033[0m type changed\n";
			$this->maybeTypeChanged();
		}
		parent::notifyNodeChangedType($node);
	}
	
	public function complainAboutAmbiguities()
	{
		$callee = $this->callee();
		if ($callee instanceof Ident && count($callee->boundNodes) > 1 && !$callee->boundTo) {
			$nodes = "";
			foreach ($callee->boundNodes as $node) {
				$nodes .= "\n- {$node->nice()}  {$node->niceType()}";
			}
			
			global $issues;
			$issues[] = new \Issue(
				'error',
				"{$this->nice()} is ambiguous. It may refer to:".$nodes,
				$this,
				$callee->boundNodes
			);
			echo "   - call complaint issued {$this->desc()}\n";
		} else {
			parent::complainAboutAmbiguities();
		}
	}
	
	public function func()
	{
		$callee = $this->callee();
		if ($callee && $callee->boundTo) return $callee->boundTo;
		return null;
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		$callee = $this->callee();
		assert($callee);
		if ($callee->boundNodes) foreach ($callee->boundNodes as $func) $func->gatherExternalNodeIDs($ids);
	}
}

class CallTypeProxy extends TypedNode
{
	public $call;
	
	public function __construct(Call $call)
	{
		$this->call   = $call;
		$this->parent = $call;
	}
	
	public function details()           { return 'proxy'; }
	public function children()          { return array(); }
	public function unconstrainedType() { return new GenericType; }
	
	public function spawnConstraints(array &$constraints)
	{
		parent::spawnConstraints($constraints);
		$constraints[] = new EqualTypeConstraint($this->call->callee(), $this->call->typeProxy);
	}
	
	public function imposeTypeConstraint(Type $type)
	{
		if ($this->call && $type instanceof FuncType) {
			//echo "- imposing constraint {$type->in()->details()} on args {$this->call->args()->details()}\n";
			$this->call->args()->imposeTypeConstraint($type->in());
			//$this->call->propagateTypeChange();
		}
		parent::imposeTypeConstraint($type);
	}
}