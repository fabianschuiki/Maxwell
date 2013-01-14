<?php
namespace Entity\Expr;
use Entity\Scope\Scope;

class TypeSpec extends Expr
{
	static public function makeFromSyntaxNode(\AST\Expr\TypeSpec $node)
	{
		$e = new self;
		$e->generateID();
		$e->setType(Type::makeFromSyntaxNode($node->getExpr()));
		$e->setRange($node->getRange());

		$args = array();
		foreach ($node->getArgs() as $arg) {
			$args[] = Type::makeFromSyntaxNode($arg);
		}
		$e->setArgs($args);

		return $e;
	}
	
	protected $type;
	protected $args;
	
	public function setType(Type $e) { $this->type = $e; $e->setParent($this); }
	public function getType() { return $this->type; }
	
	public function setArgs(array $a) { $this->args = $a; foreach($a as $ae) $ae->setParent($this); }
	public function getArgs() { return $this->args; }
	
	public function initScope(Scope &$scope)
	{
		$this->type->initScope($scope);
		foreach ($this->args as $arg)
			$arg->initScope($scope);
	}
	
	public function getChildEntities() { return array_merge(array($this->type), $this->args); }

	public function replaceChild(Entity $child, Entity $with)
	{
		if ($child === $this->type) {
			$this->setType($with);
		} else {
			$replaced = false;
			foreach ($this->args as $id => $arg) {
				if ($arg === $child) {
					$this->args[$id] = $with;
					$with->setParent($this);
					$replaced = true;
				}
			}

			if (!$replaced) {
				throw $this->makeUnknownChildException($child);
			}
		}
	}
}