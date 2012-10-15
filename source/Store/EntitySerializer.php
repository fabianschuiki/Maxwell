<?php
namespace Store;
use Coder;
use Source\File;
use Source\Range;

class EntitySerializer
{
	public $elements;
	public $entities;
	public $entity;
	
	/*
	 * ENCODING
	 */
	 
	public function encodeRootEntity(\Entity\RootEntity $entity)
	{
		$root = null;
		
		if ($entity instanceof \Entity\FunctionDefinition) {
			$root = new Coder\Element("function");
			$root->setAttribute('name', $entity->getName());
			$root->setAttribute('body', $entity->getBody()->getID());
			$root->setAttribute('scope', $entity->getScope()->getID());
			$this->encodeEntity($entity->getBody(), $root);
			$this->encodeScope($entity->getScope(), $root);
		}
		if ($entity instanceof \Entity\TypeDefinition) {
			$root = new Coder\Element("type");
			$root->setAttribute('name', $entity->getName());
			$root->setAttribute('scope', $entity->getScope()->getID());
			$this->encodeScope($entity->getScope(), $root);
			if ($entity->getSuperType())
				$root->setAttribute('superType', $entity->getSuperType());
		}
		
		if ($root) {
			$root->setAttribute('id', $entity->getID());
			$root->setAttribute('range', $entity->getRange()->toString());
			$root->setAttribute('humanRange', $entity->getHumanRange()->toString());
			$root->setAttribute('file', $entity->getRange()->getFile()->getPath());
			foreach ($entity->getSiblingEntities() as $sibling) {
				$e = $root->makeElement('sibling');
				$e->setAttribute('id', $sibling->getID());
			}
			foreach ($entity->getKnownEntities() as $known) {
				$e = $root->makeElement('known');
				$e->setAttribute('id', $known->getID());
			}
			if ($entity->analysis) {
				$this->encodeAnalysis($entity->analysis, $root);
			}
		}
		else {
			throw new \exception("Unable to encode root entity ".vartype($entity).".");
		}
		
		return $root;
	}
	
	private function encodeEntity(\Entity\Entity $entity, Coder\Element $root)
	{
		$e = null;
		if ($entity instanceof \Entity\Block) {
			$e = $root->makeElement("block");
			
			$headScope = $entity->getHeadScope();
			$tailScope = $entity->getTailScope();
			$e->setAttribute('scope-head', $headScope->getID());
			$e->setAttribute('scope-tail', $tailScope->getID());
			$this->encodeScope($headScope, $root);
			//if ($headScope != $tailScope) $this->encodeScope($tailScope, $root);
			
			foreach ($entity->getStmts() as $s) {
				$this->encodeStmtEntity($s, $root);
				$sr = $e->makeElement('stmt');
				$sr->setAttribute('id', $s->getID());
			}
		}
		
		if ($e) {
			$e->setAttribute('id', $entity->getID());
			$e->setAttribute('range', $entity->getRange()->toString());
		}
		else {
			throw new \exception("Unable to encode entity ".vartype($entity).".");
		}
	}
	
	private function encodeStmtEntity(\Entity\Stmt\Stmt $stmt, Coder\Element $root)
	{
		$e = null;
		if ($stmt instanceof \Entity\Stmt\Expr) {
			$e = $root->makeElement("expr-stmt");
			$e->setAttribute('expr', $stmt->getExpr()->getID());
			$this->encodeExprEntity($stmt->getExpr(), $root);
		}
		
		if ($e) {
			$e->setAttribute('id', $stmt->getID());
			$e->setAttribute('range', $stmt->getRange()->toString());
			if ($stmt->getHumanRange()) $e->setAttribute('humanRange', $stmt->getHumanRange()->toString());
		}
		else {
			throw new \exception("Unable to encode statement entity ".vartype($stmt).".");
		}
	}
	
	private function encodeExprEntity(\Entity\Expr\Expr $expr, Coder\Element $root)
	{
		$e = null;
		if ($expr instanceof \Entity\Expr\Constant) {
			$e = $root->makeElement("constant");
			$e->setAttribute('type', $expr->getType());
			$e->setAttribute('value', $expr->getValue());
		}
		if ($expr instanceof \Entity\Expr\Identifier) {
			$e = $root->makeElement("identifier");
			$e->setAttribute('name', $expr->getName());
			$e->setAttribute('scope', $expr->getScope()->getID());
		}
		if ($expr instanceof \Entity\Expr\VarDef) {
			$e = $root->makeElement("var");
			$e->setAttribute('name', $expr->getName());
			$e->setAttribute('scope', $expr->getScope()->getID());
			$this->encodeScope($expr->getScope(), $root);
			if ($expr->getType()) {
				$this->encodeExprEntity($expr->getType(), $root);
				$e->setAttribute('type', $expr->getType()->getID());
			}
			if ($expr->getInitial()) {
				$this->encodeExprEntity($expr->getInitial(), $root);
				$e->setAttribute('initial', $expr->getInitial()->getID());
			}
		}
		if ($expr instanceof \Entity\Expr\Operator\Binary) {
			$e = $root->makeElement("binary-op");
			$e->setAttribute('operator', $expr->getOperator());
			$this->encodeExprEntity($expr->getLHS(), $root);
			$this->encodeExprEntity($expr->getRHS(), $root);
			$e->setAttribute('lhs', $expr->getLHS()->getID());
			$e->setAttribute('rhs', $expr->getRHS()->getID());
		}
		if ($expr instanceof \Entity\Expr\MemberAccess) {
			$e = $root->makeElement("member-access");
			$e->setAttribute('name', $expr->getName());
			$this->encodeExprEntity($expr->getExpr(), $root);
			$e->setAttribute('expr', $expr->getExpr()->getID());
		}
		if ($expr instanceof \Entity\Expr\NewOp) {
			$e = $root->makeElement("new");
			$this->encodeExprEntity($expr->getExpr(), $root);
			$e->setAttribute('expr', $expr->getExpr()->getID());
		}
		
		if ($e) {
			$e->setAttribute('id', $expr->getID());
			$e->setAttribute('range', $expr->getRange()->toString());
			if ($expr->getHumanRange()) $e->setAttribute('humanRange', $expr->getHumanRange()->toString());
			if ($expr->analysis) {
				$this->encodeAnalysis($expr->analysis, $e);
			}
		}
		else {
			throw new \exception("Unable to encode expression entity ".vartype($expr).".");
		}
	}
	
	private function encodeScope(\Entity\Scope\Scope $scope, Coder\Element $root)
	{
		if ($scope instanceof \Entity\Scope\ScopeDeclaration) {
			$e = $root->makeElement('scope-declaration');
			$e->setAttribute('declares', $scope->getDeclares()->getID());
		}
		else if ($scope instanceof \Entity\Scope\ScopeRoot) {
			$e = $root->makeElement('scope-root');
			$e->setAttribute('entity', $scope->getRootEntity()->getID());
		}
		else {
			$e = $root->makeElement('scope');
		}
		
		if ($e) {
			$e->setAttribute('id', $scope->getID());
			if ($scope->getOuter()) $e->setAttribute('outer', $scope->getOuter()->getID());
			if ($scope->getUpper()) $e->setAttribute('upper', $scope->getUpper()->getID());
		}
		else {
			throw new \exception("Unable to encode scope ".vartype($scope).".");
		}
	}
	
	private function encodeAnalysis(\Analysis\Node\Node $analysis, Coder\Element $element)
	{
		if ($analysis instanceof \Analysis\Node\Expr) {
			$e = $element->makeElement("analysis-type");
			if ($i = $analysis->type->initial)  $this->encodeType($i, $e)->setAttribute('rel', 'initial');
			if ($i = $analysis->type->inferred) $this->encodeType($i, $e)->setAttribute('rel', 'inferred');
			if ($i = $analysis->type->required) $this->encodeType($i, $e)->setAttribute('rel', 'required');
		}
		if ($analysis instanceof \Analysis\Node\Identifier) {
			$e = $element->makeElement("analysis-binding");
			if ($t = $analysis->binding->target) {
				if ($t instanceof \Type\Type) {
					if (!$t instanceof \Type\Builtin) throw new \exception("Identifier can only bind to builtin types.");
					$e->setAttribute('target', "builtin:{$t->getName()}");
				} else {
					$e->setAttribute('target', $t->getID());
				}
			}
		}
		if ($analysis instanceof \Analysis\Node\RootEntity) {
			$e = $element->makeElement("analysis-type-constraints");
			foreach ($analysis->constraints->getConstraints() as $c) {
				$ce = $e->makeElement("constraint");
				foreach ($c->getEntities() as $ent) {
					$entel = $ce->makeElement("entity");
					$entel->setAttribute('id', $ent->getID());
				}
			}
		}
	}
	
	private function encodeType(\Type\Type $type, Coder\Element $element)
	{
		$e = null;
		if ($type instanceof \Type\Generic) {
			$e = $element->makeElement("type-generic");
		}
		if ($type instanceof \Type\Builtin) {
			$e = $element->makeElement("type-builtin");
			$e->setAttribute('name', $type->getName());
		}
		if ($type instanceof \Type\Defined) {
			$e = $element->makeElement("type-defined");
			$e->setAttribute('definition', $type->getDefinition()->getID());
		}
		
		if (!$e) throw new \exception("Unable to encode type ".vartype($type).".");
		return $e;
	}
	
	
	
	/*
	 * DECODING
	 */
	
	public function getEntity($id)
	{
		if ($id == $this->entity->getID()) return $this->entity;
		$e = @$this->entities[$id];
		if ($e) return $e;
		foreach ($this->entity->getKnownEntities() as $k) {
			if ($k->getID() == $id) {
				return $k;
			}
		}
		throw new \exception("Entity with ID $id is not known.");
	}
	
	public function decodeScaffolding(Coder\Element $element)
	{
		$e = null;
		switch ($element->getName()) {
			case 'function': $e = new \Entity\FunctionDefinition; break;
			case 'type':     $e = new \Entity\TypeDefinition; break;
			
			case 'block':    $e = new \Entity\Block; break;
			case 'scope':    $e = new \Entity\Scope\Scope; break;
			case 'scope-declaration': $e = new \Entity\Scope\ScopeDeclaration; break;
			case 'scope-root': $e = new \Entity\Scope\ScopeRoot; break;
			
			case 'expr-stmt': $e = new \Entity\Stmt\Expr; break;
			case 'var': $e = new \Entity\Expr\VarDef; break;
			case 'identifier': $e = new \Entity\Expr\Identifier; break;
			case 'constant': $e = new \Entity\Expr\Constant; break;
			case 'binary-op': $e = new \Entity\Expr\Operator\Binary; break;
			case 'member-access': $e = new \Entity\Expr\MemberAccess; break;
			case 'new': $e = new \Entity\Expr\NewOp; break;
		}
		if ($e) {
			if ($id = $element->getAttribute('id'))
				$e->setID($id);
			else
				throw new \exception("Element has no id: ".$this->encode($element));
		} else {
			throw new \exception("Unable to decode scaffolding for element '{$element->getName()}'.");
		}
		return $e;
	}
	
	public function decodeRootEntityScaffolding(Coder\Element $root)
	{
		$this->entity = $this->decodeScaffolding($root);
		if (!$this->entity) return null;
		
		//Decode the barebone versions of the entities and store them in an ID map.
		$this->entities = array();
		$this->elements = array();
		$this->ids = array();
		foreach ($root->getElements() as $element) {
			if ($element->getName() == 'sibling' || $element->getName() == 'known' || strpos($element->getName(), 'analysis-') === 0) continue;
			$e = $this->decodeScaffolding($element);
			$this->entities[$e->getID()] = $e;
			$this->elements[$e->getID()] = $element;
			$this->ids[] = $e->getID();
		}
	}
	
	public function decodeRootEntity(Coder\Element $root)
	{
		//Decode the child entities.
		$file = new File($root->getAttribute('file'));
		$this->decodeEntity($this->entity, $root, $this->entities, $file);
		foreach ($this->entities as $id => $e) {
			$this->decodeEntity($e, $this->elements[$id], $this->entities, $file);
		}
	}
	
	public function decodeRootEntityExternals(Coder\Element $root, EntityStore $store)
	{
		$siblings = array();
		$known = array();
		foreach ($root->getElements() as $e) {
			if ($e->getName() == 'sibling') $siblings[] = $store->getEntity($e->getAttribute('id'));
			if ($e->getName() == 'known')   $known[]    = $store->getEntity($e->getAttribute('id'));
		}
		
		$this->entity->setSiblingEntities($siblings);
		$this->entity->setKnownEntities($known);
	}
	
	public function decodeEntity(\Entity\Node $entity, Coder\Element $root, array &$entities, File $file)
	{
		if ($entity instanceof \Entity\FunctionDefinition) {
			$entity->setName($root->getAttribute('name'));
			$entity->setBody($this->getEntity($root->getAttribute('body')));
			$entity->setScope($this->getEntity($root->getAttribute('scope')));
			$entity->setFile($file);
		}
		else if ($entity instanceof \Entity\TypeDefinition) {
			$entity->setName($root->getAttribute('name'));
			$entity->setScope($this->getEntity($root->getAttribute('scope')));
			if ($s = $root->getAttribute('superType')) $entity->setSuperType($s);
		}
		else if ($entity instanceof \Entity\Block) {
			$entity->setHeadScope($this->getEntity($root->getAttribute('scope-head')));
			$entity->setTailScope($this->getEntity($root->getAttribute('scope-tail')));
			$stmts = array();
			foreach ($root->getElements() as $element) {
				if ($element->getName() == 'stmt')
					$stmts[] = $this->getEntity($element->getAttribute('id'));
			}
			$entity->setStmts($stmts);
		}
		else if ($entity instanceof \Entity\Scope\Scope) {
			if ($o = $root->getAttribute('outer')) $entity->setOuter($this->getEntity($o));
			if ($u = $root->getAttribute('upper')) $entity->setUpper($this->getEntity($u));
			if ($entity instanceof \Entity\Scope\ScopeDeclaration) {
				$entity->setDeclares($this->getEntity($root->getAttribute('declares')));
			}
			if ($entity instanceof \Entity\Scope\ScopeRoot) {
				$entity->setRootEntity($this->getEntity($root->getAttribute('entity')));
			}
		}
		else if ($entity instanceof \Entity\Stmt\Expr) {
			$entity->setExpr($this->getEntity($root->getAttribute('expr')));
		}
		else if ($entity instanceof \Entity\Expr\VarDef) {
			$entity->setName($root->getAttribute('name'));
			$entity->setScope($this->getEntity($root->getAttribute('scope')));
			if ($t = $root->getAttribute('type')) $entity->setType($this->getEntity($t));
			if ($i = $root->getAttribute('initial')) $entity->setInitial($this->getEntity($i));
		}
		else if ($entity instanceof \Entity\Expr\Identifier) {
			$entity->setName($root->getAttribute('name'));
			$entity->setScope($this->getEntity($root->getAttribute('scope')));
		}
		else if ($entity instanceof \Entity\Expr\Constant) {
			$entity->setType($root->getAttribute('type'));
			$entity->setValue($root->getAttribute('value'));
		}
		else if ($entity instanceof \Entity\Expr\Operator\Binary) {
			$entity->setOperator($root->getAttribute('operator'));
			$entity->setLHS($this->getEntity($root->getAttribute('lhs')));
			$entity->setRHS($this->getEntity($root->getAttribute('rhs')));
		}
		else if ($entity instanceof \Entity\Expr\MemberAccess) {
			$entity->setName($root->getAttribute('name'));
			$entity->setExpr($this->getEntity($root->getAttribute('expr')));
		}
		else if ($entity instanceof \Entity\Expr\NewOp) {
			$entity->setExpr($this->getEntity($root->getAttribute('expr')));
		}
		else {
			throw new \exception("Don't know how to decode ".vartype($entity).".");
		}
		
		//Decode the ranges where appropriate.
		if ($r = $root->getAttribute('range'))      $entity->setRange(Range::fromString($r, $file));
		if ($r = $root->getAttribute('humanRange')) $entity->setHumanRange(Range::fromString($r, $file));
		
		//Decode the analysis where appropriate.
		foreach ($root->getElements() as $e) {
			if ($e->getName() == "analysis-binding") {
				if ($tid = $e->getAttribute('target')) {
					$target = $tid;
					if (preg_match('/^builtin:(.*)/', $target, $matches)) {
						$entity->analysis->binding->target = \Type\Builtin::makeWithName($matches[1]);
					} else {
						$entity->analysis->binding->target = $this->getEntity($target);
					}
				}
			}
			if ($e->getName() == "analysis-type") {
				foreach ($e->getElements() as $te) {
					$type = $this->decodeType($te);
					$rel = $te->getAttribute('rel');
					if ($rel == "initial")  $entity->analysis->type->initial  = $type;
					if ($rel == "inferred") $entity->analysis->type->inferred = $type;
					if ($rel == "required") $entity->analysis->type->required = $type;
				}
			}
		}
	}
	
	public function decodeType(Coder\Element $root)
	{
		if ($root->getName() == "type-builtin") return \Type\Builtin::makeWithName($root->getAttribute('name'));
		if ($root->getName() == "type-generic") return \Type\Generic::make();
		if ($root->getName() == "type-defined") return \Type\Defined::makeWithDefinition($this->getEntity($root->getAttribute('definition')));
		throw new \exception("Unable to decode type \"{$root->getName()}\"");
	}
}